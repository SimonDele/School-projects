/**
* Name: tpnote
* Examinator : Mathieu
* Author: Simon DELECOURT et Victor LE MAISTRE
* Description: 
*/

model tpNote

global{ 
	predicate wander_around <- new_predicate("wandering");
	predicate medic_predicate <- new_predicate("has medic",true);
	predicate no_medic_predicate <- new_predicate("has medic", false) ;
	string malade <- "malade";
	int nb_people <- 2147;
	int count_infected <- 0;
	int count_healed <- 0;
	int nb_quarantined <-0;
	int nb_infected_init <- 5 ;
	int nb_doctor <- 10 ;
	int nb_volontaires <- 80;
	float step <- 1 #mn;
	float count_steps <- 0#mn update: count_steps + step;
	file roads_shapefile <- file("../includes/routes.shp");
	file buildings_shapefile <- file("../includes/batiments.shp");
	geometry shape <- envelope(roads_shapefile);
	int nb_people_infected <- nb_infected_init update: people count (each.is_infected);
	int nb_people_not_infected <- nb_people - nb_infected_init update: nb_people - nb_people_infected;
	float infected_rate update: nb_people_infected/nb_people;
	
	graph road_network;
	
	init{
		create road from: roads_shapefile;
		road_network <- as_edge_graph(road);
		create building from: buildings_shapefile with:[type::string(read ("NATURE"))]{
			if type="pharmacy" {
				color <- #darkgreen ;
				isPharmacy <- true;
			}
		}
		create people number:nb_people {
			my_house <- one_of(building where (!each.isPharmacy));
			location <- any_location_in(my_house);
			building_target <- nil;
			unique_ami <- one_of(building);
		}
		ask nb_infected_init among people {
			is_infected <- true;
			contaminates <- true;
		}
		create doctor number:nb_doctor {
			my_pharmacy <- first(building where (each.isPharmacy));
			location <- any_location_in(my_pharmacy);
		}
		
		create volontaire number:nb_volontaires{
			my_house <- one_of(building where (!each.isPharmacy));
			location <- any_location_in(my_house);
			building_target <- nil;
			unique_ami <- one_of(building);
			
		}
		
		
	}

	
	reflex end_simulation when: nb_people_infected = 0 or cycle > 840{
		do pause;
		write nb_people_infected;
	}
}

species volontaire skills:[moving]{		
	float speed <- (5 + rnd(3)) #km/#h;
	bool is_infected <- false;
	bool has_been_vaccinated <- false;
	building my_house;
	building building_target;
	building unique_ami;
	
	
	reflex choose_target when: building_target=nil{
		building_target <-one_of(building where (!each.isPharmacy));		
	}
	
	reflex quarantine {
		list<people> people_at_10 <- people at_distance 10#m;
		loop person over: people_at_10{
			if(person.is_infected){	
				if (not(person.quarantined)){
					person.contaminates <- false;
					person.quarantined<-true;
					nb_quarantined <- nb_quarantined +1;
					
				}		 	
			}
		}
	}
	
	reflex goto when: building_target !=nil {
		do goto target:building_target speed:speed on:road_network;
	}
	
	reflex arrivee when: location overlaps building_target{
		building_target <- nil;
	}
	
	aspect circle{
		draw circle(8) color:#black;
	}

	
}

species people skills:[moving]{		
	float speed <- (2 + rnd(3)) #km/#h;
	bool is_infected <- false;
	bool contaminates <-false;
	bool quarantined <- false;
	bool has_been_vaccinated <- false;
	building my_house;
	building building_target;
	building unique_ami;
	
	reflex choose_target when: building_target=nil{
		if(location overlaps my_house){
			if(flip(0.01)){
				building_target <- unique_ami;
			}
		}
		else if(location overlaps unique_ami){
			if(flip(0.01)){
				building_target <- my_house;
			}
		}
		
	}

	reflex contamination when:contaminates=true{
		list<people> people_at_10 <- people at_distance 10#m;
		loop person over: people_at_10{
			if(!person.has_been_vaccinated){
			 	if(flip(0.05)){
					ask person{
						is_infected <- true;
						contaminates<-true;
					}
				}
			}
		}
	}
	
	reflex goto when: building_target !=nil and quarantined = false {
		do goto target:building_target speed:speed on:road_network;
	}
	
	reflex arrivee when: location overlaps building_target{
		building_target <- nil;
	}
	
	aspect circle{
		if (is_infected){
			if (quarantined){
				draw circle(20) color:#purple;
			}
			else{
				draw circle(5) color:#red;
			}
			/* draw circle(5) color:quarantined ? #purple : #red;*/
		}
		else{
			draw circle(5) color:#green;
		}
	}

	
}

species doctor skills:[moving] control:simple_bdi{
	float speed <- (8) #km/#h;
	people malade_a_soigner <- nil;
	int nbMedicament;
	int nb_max_medicaments <- 20;
	float dist_minimal_soin <- 5#m;
	point random_location<-nil;
	building my_pharmacy;
	float distance_perception <-15#m;
	
	
	
	//Initialisation of the agent. At the begining, the agent just has the desire to patrol.
	init {
		nbMedicament <-0;
		do add_desire(wander_around );
		my_pharmacy <- one_of(building where (each.isPharmacy));
	}
	
	//This perceive is used to update the beliefs concerning the intern variable of the agent (the amount of water it has).
	perceive target:self {
		if(nbMedicament>0){
			do add_belief(medic_predicate);
			do remove_belief(no_medic_predicate);
		}
		if(nbMedicament=0){
			do add_belief(no_medic_predicate);
			do remove_belief(medic_predicate);
		}
	}
	
	//The doctor perceive the sick people at a certain distance. It just records the location of the fire it obsrves. When it sees a fire, it stops its intention of patroling.
	perceive target:people in: distance_perception{ 
		
		if(is_infected){
			
			focus id:"malade" var:name strength:10.0; 
			
			ask myself{
				do remove_intention(wander_around, true);
			} 
				
		}
		
	}
	
	rule belief: new_predicate(malade) new_desire: get_predicate(get_belief_with_name_op(self,malade));
	rule belief: no_medic_predicate new_desire: medic_predicate strength: 10.0;
	
	//The plan that is executed when the agent got the intention to cure people
	plan cure intention: new_predicate(malade) priority:5{
		people sick_person <- first(people where(each.name = (get_predicate(get_current_intention()).values["name_value"])));
		if(nbMedicament>0){
			if (self distance_to sick_person <= dist_minimal_soin) {
				if (sick_person != nil) {
					nbMedicament <- nbMedicament - 1;
					sick_person.is_infected <-  false;
					sick_person.contaminates <- false;
					sick_person.quarantined <- false;
					sick_person.has_been_vaccinated <- true;
					count_healed <- count_healed + 1;
			
					do remove_belief(get_predicate(get_current_intention()));
					do remove_intention(get_predicate(get_current_intention()), true);
					do add_desire(wander_around,1.0);
				}
				else{
					do remove_belief(get_predicate(get_current_intention()));
					do remove_intention(get_predicate(get_current_intention()), true);
					do add_desire(wander_around,1.0);
				}
			} else {
				do goto target: sick_person.location speed:speed on:road_network;
			}
		} 
	}
	
	
	//The plan to do when the intention is to patrol.
	plan patrolling intention:wander_around priority:1{
		if random_location=nil{
			random_location <- one_of(building where (!each.isPharmacy)).location;
		}
		else{
			if(location = random_location){
				random_location<- nil;
			}
			else{
				do goto target:random_location speed:speed on:road_network;
			}
		}	
	}
	
	//The plan to take medics when the agent get the desire of getting medicaments
    plan goFetchMeds intention: medic_predicate priority:6 {
    	if (location overlaps my_pharmacy){
    		nbMedicament <- nb_max_medicaments; 
    		do remove_intention(get_predicate(get_current_intention()), true);
    	}
    	else{
    		do goto target:my_pharmacy speed:speed on:road_network;
    	}
    }
	
	aspect circle{
		draw circle(10) color: #blue;
	}
}


species road {
	aspect geom {
		draw shape color: #black;
	}
}

species building {
	rgb color <- #gray;
	string type;
	bool isPharmacy <- false;
	
	aspect geom {
		draw shape color: color;
	}
}


experiment main_experiment type:gui{
	output {
		display map type: opengl{
			species road aspect:geom;
			species building aspect:geom;
			species people aspect:circle;		
			species doctor aspect:circle;	
			species volontaire aspect:circle;
		} 
		display necrologie_cleon {
			 chart "Illness evolution over time" type:series{
			 	data "Infected" value:  nb_people_infected/nb_people*100;	
			 	data "Not infected" value:  100-nb_people_infected/nb_people*100;		
			 	data "Healed" value:  count_healed/nb_people*100;	
			 	data "Quarantined" value: nb_quarantined/nb_people*100;
			 } 
		}
		
		display cout {
		
		 chart " <<Coût>> nécessaire à la luttre contre l'épidémie" type:series{
			 	data "Cout" value: nb_doctor*300 + count_healed*20 + nb_quarantined*50 + nb_volontaires*40;	
			 }
		}
		display nombre_malades{
			chart("Nombre de malades") type:series{
				data "Nmbre de malades" value:nb_people_infected;
			}
		}
	}

	
}

