#include <gtk/gtk.h>

#define size 12
GtkWidget *window, *mainbox;
int comp_mat[size][size+1]; char names[size][100]; int mids[size/2], cmids[size/2][size/2], mmids[size/2][size/2-1];
GtkWidget *startlabel;
GtkWidget *startbu, *nextbu1, *nextbu2, *nextbu3, *prevbu, *nextbu4, *nextbu5, *donebu;
GtkWidget *names_entries[size], *page2label, *page3label, *page4labelp, *page4labeln, *pref[size], *nameslabel[size];
GtkWidget *labelp4c, *labelp4w, *page5label, *page6label;
int count= 0; int current_person = 0; int mcounter = 0; int mmcounter = 0;
void page2(GtkWidget *widget, gpointer data);
void page3(GtkWidget *widget, gpointer data);
void page4(GtkWidget *widget, gpointer data);
void page5(GtkWidget *widget, gpointer data);
void page6(GtkWidget *widget, gpointer data);
void pref_toggled(GtkToggleButton *togglebutton, gpointer data);
void prev(GtkWidget *widget, gpointer data);
void alg(GtkWidget *widget, gpointer data);
int irving1(int [size][size+1], int [size/2][2], int [size/2], int [size/2][size/2 - 1], int [size/2], int[size/2]); //first and second part of irving's alg for mid to mid matching
int irving2(int [size][size + 1], int [size/2][2], int [size/2][size/2 - 1], int [size/2], int [size/2]);

void gp(int [size/2][size/2], int [size][size + 1], int [size][2], int [size/2]); //gale-shapely alg for matching corners to mids
void page1(GtkWidget *widget, gpointer data){
	g_print("Enter page 1\n");
	gtk_container_remove(GTK_CONTAINER(mainbox), startlabel);
	gtk_container_remove(GTK_CONTAINER(mainbox), startbu);
	for (int i = 0; i < size; i++){
		names_entries[i] = gtk_entry_new();
		char placeholder[20];
		sprintf(placeholder, "Person %d", i); //first size/2 people will site in mid
		gtk_entry_set_text(GTK_ENTRY(names_entries[i]), placeholder);
		gtk_box_pack_start(GTK_BOX(mainbox), names_entries[i], TRUE, TRUE, 0);
		
	}
	nextbu1 = gtk_button_new_with_label("Next");
	gtk_box_pack_end(GTK_BOX(mainbox), nextbu1, TRUE, TRUE, 50);
	g_signal_connect(nextbu1, "clicked" , G_CALLBACK(page2), NULL);
	gtk_widget_show_all(window);
}
void page2(GtkWidget *widget, gpointer data){
	g_print("Entering page 2 \n");
	for (int i = 0; i < size; i++){ //assinging names to array so it is easier to manage
					//also assinging namebuttons
		//names[i] = gtk_entry_get_text(GTK_ENTRY(names_entries[i]));
		const char *input = gtk_entry_get_text(GTK_ENTRY(names_entries[i]));
 		strcpy(names[i], input);
		printf("%s \t", names[i]);
	//	namebuttons[i] = gtk_button_new_with_label(input);
	}
	//removing previous widgets
	gtk_container_remove(GTK_CONTAINER(mainbox), nextbu1);
       	for (int i = 0; i < size; i++){
		gtk_container_remove(GTK_CONTAINER(mainbox), names_entries[i]);
	}
	page2label = gtk_label_new("Successfully stored names");
	nextbu2 = gtk_button_new_with_label("Ok? Continue");
	gtk_box_pack_start(GTK_BOX(mainbox), page2label, TRUE, TRUE, 100);
	gtk_box_pack_start(GTK_BOX(mainbox), nextbu2, TRUE, TRUE, 50 );
	g_signal_connect(nextbu2, "clicked", G_CALLBACK(page3), NULL);
	gtk_widget_show_all(window);
}
void pref_toggled (GtkToggleButton *togglebutton, gpointer i){ //storing the middle/corner preferences
		if (gtk_toggle_button_get_active(togglebutton))
			comp_mat[GPOINTER_TO_INT(i)][size] = 1;
		else
			comp_mat[GPOINTER_TO_INT(i)][size] = 0;
		printf("Setting %d's preference to %d \n", GPOINTER_TO_INT(i), comp_mat[GPOINTER_TO_INT(i)][size]);

}
void page3(GtkWidget *widget, gpointer data){
	g_print("Entering page 3 \n");
	gtk_container_remove(GTK_CONTAINER(mainbox), nextbu2);
	gtk_container_remove(GTK_CONTAINER(mainbox), page2label);
	page3label = gtk_label_new("The first half of that list of people will be assigned a middle seat \nand the second half a corner seat");
	for (int i =0; i < size/2; i++){ mids[i] = i; comp_mat[i][size] = 1;}
	nextbu3 = gtk_button_new_with_label("Done");
	gtk_box_pack_start(GTK_BOX(mainbox), page3label, TRUE, TRUE, 100); //even this not working
        gtk_box_pack_end(GTK_BOX(mainbox), nextbu3, TRUE, TRUE, 50 );
	//GtkWidget *nameslabel[size];
	//for (int i = 0; i < size; i ++){
	//	gtk_box_pack_start(GTK_BOX(mainbox), names_entries[i], TRUE, TRUE, 500); this is doing keeray
	//	nameslabel[i] = gtk_label_new(NULL);
//		gtk_label_set_text(GTK_LABEL(nameslabel[i]), names[i]);
		//char temp[20];
                //sprintf(temp, "%s", names[i]);
                //gtk_entry_set_text(GTK_ENTRY(nameslabel[i]), temp);

	//	gtk_box_pack_start(GTK_BOX(mainbox), nameslabel[i], TRUE, TRUE, 30);
	//	pref[i] = gtk_check_button_new_with_label(" Yes/No (Middle seat)");
	//	gtk_box_pack_start(GTK_BOX(mainbox), pref[i], TRUE, TRUE, 10);
	//	g_signal_connect(pref[i], "toggled", G_CALLBACK(pref_toggled), GINT_TO_POINTER(i));
//	}
	g_signal_connect(nextbu3, "clicked", G_CALLBACK(page5), NULL);
	gtk_widget_show_all(window);
}
void page4(GtkWidget *widget, gpointer data){
	g_print("Entering page 4\n");
//	int count1 = 0;
	gtk_container_remove(GTK_CONTAINER(mainbox), nextbu3);
	gtk_container_remove(GTK_CONTAINER(mainbox), page3label);
	//for (int i = 0; i < size; i++){
//		gtk_container_remove(GTK_CONTAINER(mainbox), nameslabel[i]);
//		gtk_container_remove(GTK_CONTAINER(mainbox), pref[i]);
//		count1 += comp_mat[i][size];
//	}
	//correct number of mids
		labelp4c = gtk_label_new("Confirmed Choices");
		gtk_box_pack_start(GTK_BOX(mainbox), labelp4c, TRUE, TRUE, 100);
		nextbu4 = gtk_button_new_with_label("Continue to seating preferences");
		gtk_box_pack_start(GTK_BOX(mainbox), nextbu4, TRUE, TRUE, 50);
		g_signal_connect(nextbu4, "clicked", G_CALLBACK(page5), NULL);
	
//	else {
//		for (int i =0; i <size; i++) comp_mat[i][size] = 0;
			
//		labelp4w = gtk_label_new("Do you want to crash my program? Enter equal number of mids and centers");
//		gtk_box_pack_start(GTK_BOX(mainbox), labelp4w, TRUE, TRUE, 100);
//		prevbu = gtk_button_new_with_label("Ok fine, go back");
//		gtk_box_pack_start(GTK_BOX(mainbox), prevbu, TRUE, TRUE, 50);
//		g_signal_connect(prevbu, "clicked", G_CALLBACK(prev), NULL);
//	}
//	gtk_widget_show_all(window);

}

void prev(GtkWidget *widget, gpointer data){
	g_print("Entering page 3 again \n");
	gtk_container_remove(GTK_CONTAINER(mainbox), labelp4w);
	gtk_container_remove(GTK_CONTAINER(mainbox), prevbu);
        page3label = gtk_label_new("Do you want a middle seat or a corner seat? \nPlease enter the correct amount this time :/");
        nextbu3 = gtk_button_new_with_label("Done");
        gtk_box_pack_start(GTK_BOX(mainbox), page3label, TRUE, TRUE, 100); //even this not working
        gtk_box_pack_end(GTK_BOX(mainbox), nextbu3, TRUE, TRUE, 50 );
        for (int i = 0; i < size; i ++){
                nameslabel[i] = gtk_label_new(NULL);
                gtk_label_set_text(GTK_LABEL(nameslabel[i]), names[i]);

                gtk_box_pack_start(GTK_BOX(mainbox), nameslabel[i], TRUE, TRUE, 30);
                pref[i] = gtk_check_button_new_with_label(" Yes/No (Middle seat)");
                gtk_box_pack_start(GTK_BOX(mainbox), pref[i], TRUE, TRUE, 10);
                g_signal_connect(pref[i], "toggled", G_CALLBACK(pref_toggled), GINT_TO_POINTER(i));
		
        }
	g_signal_connect(nextbu3, "clicked", G_CALLBACK(page4), NULL);
	gtk_widget_show_all(window);
}
void page5(GtkWidget *widget, gpointer data){
	g_print("Entering page5 for %s \n", names[current_person]);
	GtkWidget *namebuttons[size];
	for (int i = 0; i < size; i++){
		const char *input = names[i];
               // strcpy(names[i], input);
               // printf("%s \t", names[i]);
                namebuttons[i] = gtk_button_new_with_label(input);

	}


	if (current_person == 0){ //only when visiting the first time
	gtk_container_remove(GTK_CONTAINER(mainbox), page3label);
        gtk_container_remove(GTK_CONTAINER(mainbox), nextbu3);
	}
	else gtk_container_remove(GTK_CONTAINER(mainbox), nextbu5);
	page5label = gtk_label_new(NULL);
	gtk_label_set_text(GTK_LABEL(page5label), names[current_person]);
	gtk_box_pack_start(GTK_BOX(mainbox), page5label, TRUE, TRUE, 75);
	for (int i = 0; i < size; i++){
	       	gtk_box_pack_start(GTK_BOX(mainbox), namebuttons[i], TRUE, TRUE, 10);
		g_signal_connect(namebuttons[i], "clicked", G_CALLBACK(page6), GINT_TO_POINTER(i));
	}
	gtk_container_remove(GTK_CONTAINER(mainbox), namebuttons[current_person]); //removing preferance for current person to select themselves.
//	for (int p = 0; p < size; p++) g_signal_connect(namebuttons[p], "clicked", G_CALLBACK(page6), GINT_TO_POINTER(p));
//	nextbu5 = gtk_button_new_with_label("Done, go the next person");
//	gtk_box_pack_end(GTK_BOX(mainbox), nextbu5, TRUE, TRUE, 50);
//	g_signal_connect(nextbu5, "clicked", G_CALLBACK(page5), NULL);
	gtk_widget_show_all(window);		
}

void page6(GtkWidget *widget, gpointer person){
	//count %(size-1) is the pref number
	comp_mat[current_person][GPOINTER_TO_INT(person)] = count % (size- 1);
	if (comp_mat[current_person][size]){
		if (comp_mat[GPOINTER_TO_INT(person)][size]){
			mmids[mcounter][mmcounter] =GPOINTER_TO_INT(person);
			mmcounter += 1;
		}
		else {
			cmids[mcounter][count%(size-1)  -mmcounter] = GPOINTER_TO_INT(person);
		}
	}
	count += 1;
	g_print("The preference matrix is : \n"); //testing
                for (int i = 0; i < size; i++){
                for (int j = 0; j < size+1; j++) g_print("%d \t ", comp_mat[i][j]);
                g_print("\n");
                }
                for (int i = 0; i < size/2; i++){
                for (int j = 0; j < size/2-1; j++) g_print("%d \t ", mmids[i][j]);
                g_print("\n \n");
                }
                for (int i = 0; i < size/2; i++){
                for (int j = 0; j < size/2; j++) g_print("%d \t ", cmids[i][j]);
                g_print("\n \n \n");
                }


	gtk_container_remove(GTK_CONTAINER(mainbox), widget);
	
	if (count ==  size*(size-1)){
	//	if (count % size == 0) 
	//		g_callback(page5); //refreshing for new person
		g_print("The preference matrix is : \n"); //testing
		for (int i = 0; i < size; i++){
		for (int j = 0; j < size+1; j++) g_print("%d \t ", comp_mat[i][j]);
		g_print("\n");
		}
		for (int i = 0; i < size/2; i++){
                for (int j = 0; j < size/2-1; j++) g_print("%d \t ", mmids[i][j]);
                g_print("\n \n");
                }
		for (int i = 0; i < size/2; i++){
                for (int j = 0; j < size/2; j++) g_print("%d \t ", cmids[i][j]);
                g_print("\n \n \n");
                }
//		for (int i = 0; i < size/2; i++) g_print("%d \t", mids[i]);
		if (comp_mat[current_person][size]) mids[mcounter] = current_person;

		donebu = gtk_button_new_with_label("Get Stable Seating");
		gtk_box_pack_end(GTK_BOX(mainbox), donebu, TRUE, TRUE, 50);
		gtk_container_remove(GTK_CONTAINER(mainbox), page5label);
//		gtk_container_remove(GTK_CONTAINER(mainbox), nextbu5);
		page6label = gtk_label_new("Recorded preferences.\n\n\nThe output will be displayed in the terminal because I'm too lazy to output it here. \n\n\nRemember, if you did not got to sit with your friends, it's only because they ranked you low in their preference list :)");
		gtk_box_pack_start(GTK_BOX(mainbox), page6label, TRUE, TRUE, 150);
		g_signal_connect(donebu, "clicked", G_CALLBACK(alg), NULL);
	}
	else if (count % (size-1) == 0){
		mmcounter = 0;
		if (comp_mat[current_person][size]){
			mids[mcounter] = current_person;
		       	mcounter += 1;
		}
		current_person += 1;
		gtk_container_remove(GTK_CONTAINER(mainbox), page5label);
		nextbu5 = gtk_button_new_with_label("Done, go the next person");
        	gtk_box_pack_end(GTK_BOX(mainbox), nextbu5, TRUE, TRUE, 50);
		g_signal_connect(nextbu5, "clicked", G_CALLBACK(page5), NULL);
	}
	gtk_widget_show_all(window);
}


void alg(GtkWidget *widget, gpointer data){
	gtk_container_remove(GTK_CONTAINER(mainbox), page6label);
	gtk_container_remove(GTK_CONTAINER(mainbox), donebu);
	g_print("Processing data phase 1\n");
	gtk_widget_show_all(window);
	int rejmids[size/2], resultmc[size][2], resultmm[size/2][2], presult[size/2];
	
	for (int i = 0; i < size; i++){
		//comp_mat[i][i] = size + 1; already done in main
		resultmc[i][0] = size; //setting m pairing to highest pref
		resultmc[i][1] = -1; //which corresponds to -1th pref
	}
	g_print("Processing data phase 2\n");

	int x= 0;
//	for (int i = 0; i < size; i++){ //init stuff
 //               if (comp_mat[i][size]) {
  //                      mids[x] = i;
  //                      x += 1;
  //              }
  //         //      }
 //       for (int i = 0; i < size/2; i++) g_print("%d \t", mids[i]);

	//pairing mids to corner
	 gp(cmids , comp_mat, resultmc, mids);
	 g_print("Processing data phase 3\n");

    for (int i =0; i<size/2; i++) printf("%s sits with %s, preference number : %d \n", names[mids[i]], names[resultmc[mids[i]][0]], resultmc[mids[i]][1]);
    for (int i = 0; i<size/2; i++){
        rejmids[i] = 0;
        resultmm[i][0] = size;
        resultmm[i][1] = -1; 
        presult[i] = size;
    }
    if(irving1(comp_mat , resultmm, presult, mmids, rejmids, mids)){ //feels like this is also working fine
        printf("\n Phase 1 cleared.");
        for (int i=0; i<size/2;i++)  printf("\n %d asked %d", mids[i], mids[resultmm[i][0]]);
    }
    else {
        printf(" \n Sorry no stable seating exists :( \n");
        return;
    }
    printf("presult is: \n");
    for (int i = 0; i < size/2; i++) printf("%d \t", presult[i]);
    for (int i=0; i<size/2; i++){ //rejecting everyone else
        for (int j= 0; j<size/2 - 1; j++){
           //if (comp_mat[mids[i]][mids[presult[i]]] < comp_mat[mids[i]][mids[mmids[i][j]]] || comp_mat[mids[i]][mids[resultmm[i][0]]] > comp_mat[mids[i]][mids[mmids[i][j]]]){
            if (mmids[i][j] != size){
               if (comp_mat[mids[i]][mids[presult[i]]] < comp_mat[mids[i]][mids[mmids[i][j]]] || comp_mat[mids[i]][mids[resultmm[i][0]]] > comp_mat[mids[i]][mids[mmids[i][j]]]){ 
               printf("in at i %d j %d \t", i, j);
               printf("%d, %d, %d, %d \n", comp_mat[mids[i]][mids[presult[i]]],comp_mat[mids[i]][mids[resultmm[i][0]]], comp_mat[mids[i]][mids[mmids[i][j]]], mmids[i][j]);
                    for (int k= 0; k<size/2 - 1; k++){ //a rejected b, so b must also then reject a
                        if (mmids[mmids[i][j]][k] == i){
                            mmids[mmids[i][j]][k] = size;
                            rejmids[mmids[i][j]] += 1;
                            break;
                        }
                    }
                    mmids[i][j] = size;
                    rejmids[i]+= 1;
            }
            printf("mmids are: \n");
            for (int i =0; i < size/2; i++){
                for (int j =0; j < size/2 -1 ; j++) printf("%d \t", mmids[i][j]);
                printf("\n");
            }
       }
   }
}
	/*

    //pairing mids with mids
    if(irving1(comp_mat , resultmm, presult, mmids, rejmids, mids)){
        printf("\n Phase 1 cleared.");
        for (int i=0; i<size/2;i++)  printf("\n %s asked %s", names[mids[i]], names[mids[resultmm[i][0]]]);
    }
    else {
        printf(" \n Sorry no stable seating exists :( \n");
        return;
    }

    for (int i=0; i<size/2; i++){ //rejecting everyone else
       for (int j= 0; j<size/2 - 1; j++){
           if (comp_mat[mids[i]][mids[presult[i]]] < comp_mat[mids[i]][mids[mmids[i][j]]] || resultmm[i][1] > comp_mat[mids[i]][mids[mmids[i][j]]]){
               printf("in at i %d j %d", i, j);
                if (mmids[i][j] != size){mmids[i][j] = size;
                    rejmids[i]+= 1;
                }
           }
       }
   } */
   printf("\n This is after everyone is rejected \n");
   for (int i=0; i<size/2; i++){ 
       for (int j= 0; j<size/2 -1; j++) printf("%d", mmids[i][j]);
       printf("\t");
    }
    printf("rejcount");
    for (int i=0; i<size/2; i++) printf("%d", rejmids[i]);
    if (irving2(comp_mat,resultmm, mmids, rejmids, mids)){
        printf(" \nA stable seating exists and it is the following : \n");
        int finalmm [size/2]; //creating a non repeating list of m - m pairing
        for (int j = 0; j < size/2; j ++) finalmm[j] = 0;
        int k = 0;
        for (int i = 0; i <size/2; i++){ 
            //equating first pair, setting to -1 in the pair index
            if (finalmm[i] == -1){
                printf("\n %d in if con \n", i);
                continue;

            } 
            finalmm[i] = mmids[i][0];
            finalmm[mmids[i][0]] = -1;
            printf("%d out of if %d %d",i, finalmm[i], finalmm[mmids[i][0]] );
        }
        for (int i=0; i<size/2; i++) printf("%d final %d \t", i, finalmm[i]);
        printf("\n");
        for (int i=0; i< size/2; i++){
            if (finalmm[i] == -1) continue;
            printf(" %s \t %s \t", names[resultmc[mids[i]][0]], names[mids[i]]);
            printf(" %s \t %s \t", names[mids[mmids[i][0]]], names[resultmc[mids[mmids[i][0]]][0]]);
            printf("\n");
        }
    }
    else  printf("\nSorry no stable matching for 4 exists :( ");
    gtk_main_quit();
}
void gp(int m[size/2][size/2], int comp[size][size + 1], int resmc[size][2], int mconv[size/2]){
/*m is the pref of m' to  corns
comp is complete matrix
resmc is result of pairings, first coloumn is pairing to person, second row is pref num
mconv takes m and gives m' */

    for (int i =0; i <size/2; i++){ //looping through mids and checking if anyone is rejected
        while (resmc[mconv[i]][0] == size){
            resmc[mconv[i]][1] += 1; //pref of m'i is increased by 1
            //m[i][resmc[mconv[i]][1]] is the new prefered cperson
            //if cperson prefers m'(i) over his current pref = resmc[cperson][1]
            if (resmc[m[i][resmc[mconv[i]][1]]][1] == -1){ //accounting for the base case
                resmc[m[i][resmc[mconv[i]][1]]][1] = comp[m[i][resmc[mconv[i]][1]]][mconv[i]];
                resmc[m[i][resmc[mconv[i]][1]]][0] = mconv[i];
                resmc[mconv[i]][0] = m[i][resmc[mconv[i]][1]];
                gp(m, comp, resmc, mconv);
            }
            if (resmc[m[i][resmc[mconv[i]][1]]][1] > comp[m[i][resmc[mconv[i]][1]]][mconv[i]]){
                resmc[resmc[m[i][resmc[mconv[i]][1]]][0]][0] = size; //the previous person is rejected
                resmc[m[i][resmc[mconv[i]][1]]][1] = comp[m[i][resmc[mconv[i]][1]]][mconv[i]]; //new pref number is set for corner
                resmc[m[i][resmc[mconv[i]][1]]][0] = mconv[i]; //new pref is set for corner
                resmc[mconv[i]][0] = m[i][resmc[mconv[i]][1]]; //pref set for mid
                //dont need to set pref number for mid since that was done at the start of while loop
                gp(m , comp, resmc, mconv); //the process is repeaeted
            }
        }
    }
}


int irving1(int comp[size][size + 1], int resmm[size/2][2], int presm[size/2], int midmids[size/2][size/2 - 1], int rejcount[size/2], int mconv[size/2]){
    //resmm is proposal, presm is proposed
    printf("\nAttempting to pair mids to mids \n");
    for (int i = 0; i<size/2; i++){ //just some print stuff to check
        printf("resmm");
        for (int j = 0; j<size/2; j++) printf("%d %d \t", resmm[j][0], resmm[j][1]);
        printf("\n");
        printf("presm");
        for (int j = 0; j<size/2; j++) printf("%d \t", presm[j]);
        printf("\n");
        printf("midmids");
        for (int j =0; j<size/2; j++) printf("%d %d %d \t", midmids[j][0],midmids[j][1],midmids[j][2]);
        while (resmm[i][0]== size){
           printf("find pair for %d, try %d", i, resmm[i][1]);
            resmm[i][1] += 1;
            if (resmm[i][1] == size/2 - 1) return 0; //if someone is rejected completely
            //new person is mmids[i][resmm[i][1]]]
            if (presm[midmids[i][resmm[i][1]]] == size){ //if that person is currently unproposed
               printf("in %d %d \n", i,midmids[i][resmm[i][1]]); 
                presm[midmids[i][resmm[i][1]]] = i;
                resmm[i][0] = midmids[i][resmm[i][1]]; //setting new current proposal  
                return irving1( comp , resmm, presm, midmids, rejcount, mconv);
            }
            else if (comp[mconv[midmids[i][resmm[i][1]]]][mconv[presm[midmids[i][resmm[i][1]]]]] > comp[mconv[midmids[i][resmm[i][1]]]][mconv[i]]){ //if that person is more preferred
              printf("in 2  %d %d \n", i,midmids[i][resmm[i][1]]);
              resmm[presm[midmids[i][resmm[i][1]]]][0] = size; //previous person is rejected
               // if (rejcount[presm[mmids[i][resmm[i][1]]]] == size/2 - 1) return 0; //is he completely rejected?
               if (resmm[presm[midmids[i][resmm[i][1]]]][1] == size/2 - 2) return 0;
	 	 presm[midmids[i][resmm[i][1]]] = i; //setting new person for proposed
                resmm[i][0] = midmids[i][resmm[i][1]]; //setting new person for proposal 
                return irving1(comp ,resmm, presm, midmids, rejcount, mconv);
            }
        }
    }
    return 1;
}

int irving2(int comp[size][size + 1], int resmm[size/2][2], int mmid[size/2][size/2 - 1], int rejcount[size/2], int mconv[size/2]){
    int count = 0; int temp;
    for (int i=0; i<size/2; i++){ //rearranging
        count = 0;
        for (int j=0; j < size/2 - 1; j++){
            if (mmid[i][j] == size){
                count += 1;
                continue;
            }
            mmid[i][j-count] = mmid[i][j];
            if (j >= size/2 - 1 -rejcount[i]) mmid[i][j] = size;
            //continue;}
        }
    }
 //   printf("The rearranged mid is: \n");
  //  for (int i =0; i<size/2; i++){
   //     for (int j=0; j<size/2 - 1; j++) printf("%d \t", mmids[i][j]);
    //    printf("\n");
   // } 
    for (int i=0; i<size/2; i++){ //checking if any empty or final result is reached    
     //   printf("in 4");
     //   printf("rejcount %d", rejcount[i]);
        if (rejcount[i] == size/2 - 1) return 0;
        if (rejcount[i] <= size/2 - 1 - 2) break;
        if (i == size/2 - 1) return 1;
    }
  //  printf(" \n This is mmids after rearagning. \n");
  //  printf("\n this is after everyone is rejected \n");
   // for (int i=0; i<size/2; i++){ 
    //   for (int j= 0; j<size/2 - 1; j++) printf("%d", mmids[i][j]);
     //  printf("\t");
  //  }
    int p[size + 1][2]; //int c = 0;
    for (int i = 1; i<size + 1;i++){
        for (int j=0; j<2; j++) p[i][j] = size;
    }
    for (int i=0; i<size; i++){ //the first person who has atleast 2 preferences left
        if (mmids[i][1] != size){
            p[0][0] = i;
            p[0][1] = mmid[i][1];
            break;
        }
    }
    int k=1;
    p[1][0] = mmid[p[0][1]][size/2 - 2 -rejcount[p[0][1]]]; //base case
    while (p[0][0] !=  p[k][0]){
        p[k-1][1] = mmid[p[k-1][0]][1];
       
       p[k][0] = mmid[p[k-1][1]][size/2 - 2 -rejcount[p[k-1][1]]];
       k += 1;
    }
    for (int i=0; i<k; i++ ){
        mmid[p[k][1]][p[k+1][0]] = size;
        mmid[p[k+1][0]][p[k][1]] = size;
        rejcount[p[k][1]] += 1;
        rejcount[p[k+1][0]] += 1;
    }
    return irving2(comp, resmm, mmid, rejcount, mconv);
}

int main(int argc, char *argv[]) {
gtk_init(&argc, &argv);
window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_default_size(GTK_WINDOW(window), 800,700);
gtk_window_set_title(GTK_WINDOW(window), "Ideal Seating Program");
//Create a scrolled window
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);

    // Add the scrolled window to main window
    gtk_container_add(GTK_CONTAINER(window), scrolled_window);

    // Set the scrolled window's policy to automatic for both horizontal and vertical scrollbars
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);


for (int i =0; i < size; i++) comp_mat[i][i] = size + 1;

mainbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

startlabel = gtk_label_new("Welcome to the ideal seating program :D ");

gtk_box_pack_start(GTK_BOX(mainbox), startlabel, TRUE, TRUE, 100);
startbu = gtk_button_new_with_label("Start");
gtk_box_pack_end(GTK_BOX(mainbox), startbu, TRUE, TRUE, 50);






g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
g_signal_connect(startbu, "clicked", G_CALLBACK(page1), NULL);
gtk_container_add(GTK_CONTAINER(scrolled_window), mainbox);
gtk_widget_show_all(window);
gtk_main();
return 0;
}
