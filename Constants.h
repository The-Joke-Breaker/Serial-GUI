//Constants.h
//Globale konstanter placeres her.
//Programmeret af Mathias Steentoft og Lars Jensen.
#include <gtk/gtk.h> //Indlæs GTK+ biblioteket
#include <glib/gprintf.h> //Indlæs glib funktioner til glib strings

  GtkWidget *window; //Definer GTK+ objekt window
  GtkWidget *tableprogram; //Definer GTK+ objekt tableprogram
  
  GtkWidget *tablemenu; //Definer GTK+ objekt tablemenu
  GtkWidget *table; //Definer GTK+ objekt table
  
  GtkWidget *menubar; //Definer GTK+ objekt menubar
  GtkWidget *menu; //Definer GTK+ objekt menu
  GtkWidget *fenuport; //Definer GTK+ objekt fenuport
  GtkWidget *fepo; //Definer GTK+ objekt fepo
  GtkWidget *quit; //Definer GTK+ objekt quit
  GtkWidget *menuport; //Definer GTK+ objekt menuport
  GtkWidget *mepo; //Definer GTK+ objekt menuport
  GtkWidget *USB0; //Definer GTK+ objekt USB0
  GtkWidget *USB1; //Definer GTK+ objekt USB1
  GtkWidget *menuportbut; //Definer GTK+ objekt menuportbut
  GtkWidget *vbox; //Definer GTK+ objekt menuportbut
  GtkWidget *savebut;
  GtkWidget *loadbut;

  GtkWidget *labelsend; //Definer GTK+ objekt labelsend
  GtkWidget *label1; //Definer GTK+ objekt label1
  GtkWidget *label2; //Definer GTK+ objekt label2
  GtkWidget *label3; //Definer GTK+ objekt label3

  GtkWidget *entrysend; //Definer GTK+ objekt entrysend
  GtkWidget *entryport; //Definer GTK+ objekt entryport
  GtkWidget *entry1; //Definer GTK+ objekt entry1
  GtkWidget *entry2; //Definer GTK+ objekt entry2
  GtkWidget *entry3; //Definer GTK+ objekt entry3

  GtkEntryBuffer *buffersend;  //Definer GTK+ buffer string ved navn buffersend til en linje der kan skrives på
  GtkEntryBuffer *bufferport;  //Definer GTK+ buffer string ved navn bufferport til en linje der kan skrives på
  GtkEntryBuffer *buffer1; //Definer GTK+ buffer string ved navn buffer1 til en linje der kan skrives på
  GtkEntryBuffer *buffer2; //Definer GTK+ buffer string ved navn buffer2 til en linje der kan skrives på
  GtkEntryBuffer *buffer3; //Definer GTK+ buffer string ved navn buffer3 til en linje der kan skrives på

  GtkWidget *send; //Definer GTK+ objekt send
  GtkWidget *stop; //Definer GTK+ objekt stop
  
  GtkWidget *frame1; //Definer GTK+ objekt frame1
  GtkWidget *frame2; //Definer GTK+ objekt frame2

   char port[255] = "/dev/ttyACM0"; //Sætter standard porten til Arduino seriel porten
   char *start = "ST\aRT\a"; //besked der sendes før første sending
	char *filename;
	char key1[6];
	char key2[6];
	char key3[6];
	gchar gkey1[6];
	gchar gkey2[6];
	gchar gkey3[6];
	char buff[255] = {0}; //Filbuffer
