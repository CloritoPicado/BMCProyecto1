#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

GtkWidget *window,*scale,*scrollGenes,*siguienteGenes, *paneGenes;
//Lista que guarda los nombres de los genes
char listaNombres[100][10];

//Crea un viewport y un panel adentro del scroll window para poder insertar objetos huérfanos.

void crearScrollGenes()
{
    
    GtkWidget *viewportGenes = gtk_viewport_new (0,0);
    gtk_container_add (GTK_CONTAINER (scrollGenes), viewportGenes);
    paneGenes = gtk_fixed_new ();
    gtk_container_add (GTK_CONTAINER (viewportGenes), paneGenes);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrollGenes),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC); 
    

    gtk_widget_show(viewportGenes);
    gtk_widget_show(paneGenes);
}

//Listener de los text entry cuando cambia su valor
void valorCambiado(GtkWidget *widget, gpointer *data)
{
	char nombre[10];
	sprintf(nombre, "%s", gtk_entry_get_text(widget));
	strcpy(listaNombres[(int)data], nombre);
    g_print("%s", listaNombres[(int)data]);
}

//Crea numero cantidad de labels y un text entries huerfanos
void insertarGenes(int numero)
{
	char nombre[10];
	for(int a = 0; a<numero; a++)
	{	

	   GtkWidget *huerfanoTemp = gtk_entry_new();
	   sprintf(nombre, "G%d", a);
	   gtk_entry_set_text(huerfanoTemp, nombre);
       gtk_fixed_put(paneGenes, huerfanoTemp, 250, 40*(a)+35);
       gtk_entry_set_max_length (huerfanoTemp,10);
       gtk_entry_set_width_chars(huerfanoTemp,10);
       gtk_widget_show(huerfanoTemp);
       g_signal_connect (huerfanoTemp, "changed",valorCambiado, a);
       strcpy(listaNombres[a], nombre);


       GtkWidget *labelHuerfano = gtk_label_new("");
       sprintf(nombre, "Gen %d: ", a);
       gtk_label_set_text(labelHuerfano,nombre);
       gtk_fixed_put(paneGenes, labelHuerfano, 180, 40*(a)+40);
       gtk_widget_show(labelHuerfano);
	}
	
}

//Elimina los hijos de un contenedor aunque sean huérfanos
void destruirHijos(GtkWidget *container)
{

    GList *hijos;
    hijos = gtk_container_get_children(GTK_CONTAINER(container));
    int tamanho = g_list_length(hijos);
    for(int i = 0; i != tamanho; i++){
        gtk_widget_destroy(GTK_WIDGET(g_list_nth(hijos, i)->data));        
    }
    g_list_free(hijos);
}

/*****************************Listeners**************************/
void on_botonGenes_clicked()
{
	
}

void on_scale_value_changed()
{
	int valor = (int)gtk_range_get_value(GTK_RANGE(scale));
	destruirHijos(paneGenes);
	insertarGenes(valor);
}
/*****************************</Listeners>***********************/

int main(int argc, char *argv[])
{

    GtkBuilder      *builder; 
	gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/UI.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "ventanaGenes")); 

    scale = GTK_WIDGET(gtk_builder_get_object(builder, "scale"));
    scrollGenes = GTK_WIDGET(gtk_builder_get_object(builder, "scrollGenes"));
    GtkWidget *botonGenes = GTK_WIDGET(gtk_builder_get_object(builder, "botonGenes"));
    
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);    
    gtk_widget_show(window);   
    crearScrollGenes();
    insertarGenes(1);
    //g_print ("%s\n", "holis");
    gtk_main();
    
 

    return 0;
} 