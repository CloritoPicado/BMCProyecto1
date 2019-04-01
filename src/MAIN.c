#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

GtkWidget *window,*scale,*scrollGenes,*siguienteGenes, *paneGenes , *scrollProbabilidad, *paneProbalidad, *ventanaProbabilidad, *box;
//Lista que guarda los nombres de los genes
char listaNombres[100][10];
float listaProbabilidades[625];
int cantidadGenes = 4;

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

void crearScrollProbabilidad()
{
    
    GtkWidget *viewportProbabilidad = gtk_viewport_new (0,0);
    gtk_container_add (GTK_CONTAINER (scrollProbabilidad), viewportProbabilidad);
    paneProbalidad = gtk_fixed_new ();
    gtk_container_add (GTK_CONTAINER (viewportProbabilidad), paneProbalidad);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrollGenes),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC); 
    

    gtk_widget_show(viewportProbabilidad);
    gtk_widget_show(paneProbalidad);
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

void crearMatriz()
{
	GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing (GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing (GTK_GRID(grid), 10);

    //const GdkRGBA *color;
    for(int i = 1; i < cantidadGenes+1; i++)
    {

        for(int j = 1; j < cantidadGenes+1; j++)
        {

            if(i==1)
            {

                GtkWidget *label = gtk_label_new(listaNombres[j-1]);
                gtk_label_set_width_chars(GTK_LABEL(label), 10);
                gtk_widget_set_size_request(label, 500/(cantidadGenes+4), 500/(cantidadGenes+4));
                box = gtk_box_new(0, 0);
                gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                gtk_grid_attach(GTK_GRID(grid), box, 0, j, 1, 1);
                
                //gdk_rgba_parse (color, "#48D1CC");
                //gtk_widget_override_background_color (box,GTK_STATE_NORMAL, color);                

                gtk_widget_show (label);
                gtk_widget_show (box);
            }
            if(j==1)
            {

                GtkWidget *label = gtk_label_new(listaNombres[i-1]);
                gtk_label_set_width_chars(GTK_LABEL(label), 10);
                gtk_widget_set_size_request(label, 500/(cantidadGenes+4), 500/(cantidadGenes+4));
                box = gtk_box_new(0, 0);
                gtk_box_pack_start(GTK_BOX(box), label, 0,0,0);  
                gtk_grid_attach(GTK_GRID(grid), box, i, 0, 1, 1);
                //const GdkRGBA *color2;
                //gdk_rgba_parse (color, "#d91e18");
                //gtk_widget_override_background_color (box,GTK_STATE_NORMAL, color); 

                gtk_widget_show (label);
                gtk_widget_show (box);
            }                      
            	GtkWidget *entry = gtk_entry_new();
            	gtk_entry_set_text(entry, "0.5");
            	gtk_entry_set_max_length (entry,8);
       			gtk_entry_set_width_chars(entry,8);
            	gtk_widget_set_size_request(entry, 100/(cantidadGenes+4), 100/(cantidadGenes+4));
                box = gtk_box_new(0, 0);
                gtk_box_pack_start(GTK_BOX(box), entry, 0,0,0);  
                gtk_grid_attach(GTK_GRID(grid), box, i, j, 1, 1);

                //gdk_rgba_parse (color, "#FFFFFF");
                //gtk_widget_override_background_color (box,GTK_STATE_NORMAL, color); 


                gtk_widget_show (entry);
                gtk_widget_show (box);  
        }
    }
    gtk_container_add (GTK_CONTAINER (paneProbalidad), grid);
    gtk_widget_show (grid);
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
	gtk_widget_hide(window);
	crearScrollProbabilidad();
	crearMatriz();
    gtk_widget_show(ventanaProbabilidad);
}

void on_scale_value_changed()
{
	int valor = (int)gtk_range_get_value(GTK_RANGE(scale));
	destruirHijos(paneGenes);
	insertarGenes(valor);
	cantidadGenes = valor;
}
/*****************************</Listeners>***********************/

int main(int argc, char *argv[])
{

    GtkBuilder      *builder; 
	gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/UI.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "ventanaGenes")); 
    ventanaProbabilidad = GTK_WIDGET(gtk_builder_get_object(builder, "ventanaProbabilidad"));

    scale = GTK_WIDGET(gtk_builder_get_object(builder, "scale"));
    scrollGenes = GTK_WIDGET(gtk_builder_get_object(builder, "scrollGenes"));
    scrollProbabilidad = GTK_WIDGET(gtk_builder_get_object(builder, "scrollProbabilidad"));
    GtkWidget *botonGenes = GTK_WIDGET(gtk_builder_get_object(builder, "botonGenes"));
    
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);    
    gtk_widget_show(window);   
    crearScrollGenes();
    insertarGenes(4);
    //g_print ("%s\n", "holis");
    gtk_main();
    
 

    return 0;
} 