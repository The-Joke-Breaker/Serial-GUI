#include "serialgui.h" //Indlæs Serial-backend.h der indeholder Seriel kommandoerne
int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv); 													//Initialiserer GTK+ bibloteket

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 							//Lav nyt vindue ved navn window
  gtk_window_set_title(GTK_WINDOW(window), "Seriel GUI V1.3");				//Sæt titlen af vinduet
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE); 						//Vinduet kan ikke ændres i størrelse

  tableprogram = gtk_table_new(1, 3, FALSE); 								//Lav en ny tabel ved navn tableprogram med 1 kolonne og 3 rækker uden ens sektioner
  gtk_table_set_row_spacings(GTK_TABLE(tableprogram), 2);		 			//Mindste afstand mellem rækker er lig med 2
  gtk_container_add(GTK_CONTAINER(window), tableprogram); 					//Placer tabellen i vinduet ved navn window

  frame1 = gtk_frame_new("Send signal til cafébrik nummer");				//Lav en ny ramme ved navn frame1 med en titel
  gtk_frame_set_shadow_type(GTK_FRAME(frame1), GTK_SHADOW_ETCHED_IN);		// Rammestil sat til GTK_SHADOW_ETCHED_IN
  gtk_table_attach(GTK_TABLE(tableprogram), frame1, 0, 1, 1, 2, 			//sæt objekt mellem række 0 og 1, kolonne 0 og 1 i tableprogram
        GTK_FILL | GTK_SHRINK , GTK_FILL | GTK_SHRINK, 0, 0);
  frame2 = gtk_frame_new("Cafebrik ID liste");								//Lav en ny ramme ved navn frame2 med en titel
  gtk_frame_set_shadow_type(GTK_FRAME(frame2), GTK_SHADOW_IN); 				// Rammestil sat til GTK_SHADOW_IN
  gtk_table_attach(GTK_TABLE(tableprogram), frame2, 0, 1, 2, 3, 			//sæt objekt mellem række 0 og 1, kolonne 1 og 2 i tableprogram
        GTK_FILL | GTK_SHRINK , GTK_FILL | GTK_SHRINK, 50, 0);

      tablemenu = gtk_table_new(4, 1, FALSE); 								//Lav en ny tabel ved navn tablemenu med 4 kolonner og 1 række uden ens sektioner
  gtk_container_add(GTK_CONTAINER(frame1), tablemenu); 						//Placer i objekt frame1

    table = gtk_table_new(2, 3, FALSE);										//Lav en ny tabel ved navn table med 2 kolonner og 3 rækker uden ens sektioner
  gtk_table_set_row_spacings(GTK_TABLE(table), 2); 							//Mindste afstand mellem rækker er lig med 2
gtk_table_set_col_spacings(GTK_TABLE(table), 2);  							//Mindste afstand mellem kolonner er lig med 2
  gtk_container_add(GTK_CONTAINER(frame2), table); 							//Placer i objekt frame2

  label1 = gtk_label_new("1"); 												//Lav markat ved navn label 1 med indhold "1"
  label2 = gtk_label_new("2"); 												//Lav markat ved navn label 2 med indhold "2"
  label3 = gtk_label_new("3"); 												//Lav markat ved navn label 3 med indhold "3"

  gtk_table_attach(GTK_TABLE(table), label1, 0, 1, 0, 1, 					//sæt objekt mellem række 0 og 1, kolonne 0 og 1 i table
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);					//Sæt minimum 5 afstand til andre objekter, på både x og y akserne
  gtk_table_attach(GTK_TABLE(table), label2, 0, 1, 1, 2, 					//sæt objekt mellem række 0 og 1, kolonne 1 og 2 i table
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
  gtk_table_attach(GTK_TABLE(table), label3, 0, 1, 2, 3, 					//sæt objekt mellem række 0 og 1, kolonne 2 og 3 i table
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

  buffer1 = gtk_entry_buffer_new ("AB2831",7);								//Lav en buffer string ved navn buffer1 til en linje der kan skrives på
  buffer2 = gtk_entry_buffer_new ("AB2832",7);								//Lav en buffer string ved navn buffer2 til en linje der kan skrives på
  buffer3 = gtk_entry_buffer_new ("KODE03",7);								//Lav en buffer string ved navn buffer3 til en linje der kan skrives på
  entry1 = gtk_entry_new_with_buffer(buffer1);								//Lav en linje der kan skrives på ved navn entry1, som bruger buffer1
  entry2 = gtk_entry_new_with_buffer(buffer2);								//Lav en linje der kan skrives på ved navn entry2, som bruger buffer2
  entry3 = gtk_entry_new_with_buffer(buffer3);								//Lav en linje der kan skrives på ved navn entry3, som bruger buffer3

  gtk_table_attach(GTK_TABLE(table), entry1, 1, 2, 0, 1, 					//sæt objekt mellem række 1 og 2, kolonne 0 og 1 i table
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
  gtk_table_attach(GTK_TABLE(table), entry2, 1, 2, 1, 2, 					//sæt objekt mellem række 1 og 2, kolonne 1 og 2 i table
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
  gtk_table_attach(GTK_TABLE(table), entry3, 1, 2, 2, 3, 					//sæt objekt mellem række 1 og 2, kolonne 2 og 3 i table
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
      
  labelsend = gtk_label_new("Send"); 										//Lav markat ved navn labelsend
  
  buffersend = gtk_entry_buffer_new ("1",1);								//Lav en buffer string ved navn buffersend til en linje der kan skrives på
  entrysend = gtk_entry_new_with_buffer(buffersend); 						//Lav en linje der kan skrives på ved navn entrysend, som bruger buffersend
  
  send = gtk_button_new_with_label("Tænd"); 								//lav en knap ved navn send der har et markat "Tænd"
    g_signal_connect(G_OBJECT(send), "clicked", G_CALLBACK(taend), NULL); 	//Hvis man trykker på knappen aktiverer man funktion taend uden at sende nogen ekstra data.
 
  stop = gtk_button_new_with_label("Sluk"); 								//lav en knap ved navn send der har et markat "Sluk"
    g_signal_connect(G_OBJECT(stop), "clicked", G_CALLBACK(sluk), NULL); 	//Hvis man trykker på knappen aktiverer man funktion sluk uden at sende nogen ekstra data.

  gtk_table_attach(GTK_TABLE(tablemenu), labelsend, 0, 1, 0, 1, 			//sæt objekt mellem række 0 og 1, kolonne 0 og 1 i tablemenu
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
  gtk_table_attach(GTK_TABLE(tablemenu), entrysend, 1, 2, 0, 1, 			//sæt objekt mellem række 1 og 2, kolonne 0 og 1 i tablemenu
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
  gtk_table_attach(GTK_TABLE(tablemenu), send, 2, 3, 0, 1, 					//sæt objekt mellem række 2 og 3, kolonne 0 og 1 i tablemenu
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
  gtk_table_attach(GTK_TABLE(tablemenu), stop, 3, 4, 0, 1, 					//sæt objekt mellem række 3 og 4, kolonne 0 og 1 i tablemenu
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
 
  vbox = gtk_vbox_new(FALSE, 0);											//lav lodret boks, uden tvunget ens størrelser af elementer og 0 mellemrum
  gtk_table_attach(GTK_TABLE(tableprogram), vbox, 0, 1, 0, 1, 				//sæt objekt mellem række 0 og 1, kolonne 0 og 1 i tableprogram
        GTK_FILL | GTK_SHRINK , GTK_FILL | GTK_SHRINK, 0, 0);
      
  menubar = gtk_menu_bar_new();												//Lav en menubar
  
  fenuport = gtk_menu_new();												//lav en menu
  fepo = gtk_menu_item_new_with_label("Filer");								//Navngiv menuobjekt
  quit = gtk_menu_item_new_with_label("Luk programmet");
  
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(fepo),fenuport);					//Sæt menuobjekt som undermenu ved navn fenuport
  gtk_menu_shell_append(GTK_MENU_SHELL(fenuport),quit);						//Placer menuobjekt i fenuport menuen
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar),fepo);
  
  menuport = gtk_menu_new();
  mepo = gtk_menu_item_new_with_label("Konfiguration");
  USB0 = gtk_menu_item_new_with_label("/dev/ttyUSB0");
  USB1 = gtk_menu_item_new_with_label("/dev/ttyUSB1");
  menuportbut = gtk_menu_item_new_with_label("Sæt port manuelt");
  savebut = gtk_menu_item_new_with_label("Gem konfigurationsfil");
  loadbut = gtk_menu_item_new_with_label("Indlæs konfigurationsfil");
  
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(mepo),menuport);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuport),USB0);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuport),USB1);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuport),menuportbut);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuport),savebut);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuport),loadbut);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar),mepo);
  gtk_box_pack_start(GTK_BOX(vbox),menubar, FALSE, FALSE, 0); 				//Placerer menubaren i en boks. Menuobjekterne skal ikke udvide sig selv automatisk vandret. Tillad menuobjekterne at røre kanten af menubaren.

  g_signal_connect(G_OBJECT(USB0), "activate", G_CALLBACK(ttyUSB0), NULL);	//Hvis man trykker på knappen aktiverer man funktion ttyUSB0 uden at sende nogen ekstra data.
  g_signal_connect(G_OBJECT(USB1), "activate", G_CALLBACK(ttyUSB1), NULL);	//Hvis man trykker på knappen aktiverer man funktion ttyUSB1 uden at sende nogen ekstra data.
  g_signal_connect(G_OBJECT(menuportbut), "activate", G_CALLBACK(setport), NULL);
  g_signal_connect(G_OBJECT(savebut), "activate", G_CALLBACK(save), NULL);
  g_signal_connect(G_OBJECT(loadbut), "activate", G_CALLBACK(load), NULL);
  g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(gtk_main_quit), NULL); //Luk programmet hvis der trykkes på quit.
  
  gtk_widget_show_all(window);												//Vis alt inde i vinduet ved navn Window

  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL); 	//Tillader programmet at modtage "destroy" signal der lukker programmet.

autoload(); //Indlæs konfigurationsfilen.

  gtk_main(); //Kør GTK+ loopet

  return 0; //Stop hvis programmet forlader GTK+ loopet+
}
