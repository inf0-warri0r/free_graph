/*
*Author :Tharindra Galahena
*Project:free_graph - graph drawing library for c/c++ (linux) -demo app
*Date   :28/06/2012
*/

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>
#include <glib.h>

#include <free_graph.h>

struct graph *g;

GtkWidget *window_main;
GtkWidget *box_main;
GtkWidget* image_headder;
GtkWidget* text_x_max;
GtkWidget* text_x_min;
GtkWidget* text_y_max;
GtkWidget* text_y_min;


double func1(double x){	
	return (x - 1)*(x - 2)*(x - 3)*(x - 4);
}
double func2(double x){	
	return x*x*x + 3*x*x + 4;
}
double func3(double x){
	return sin(x*3.14/180.0);
}
double func4(double x){
	return log(x);
}
double func5(double x){
	return cos(x*3.14/180.0);
}
double func6(double x){
	return tan(x*3.14/180.0);
}
void re_draw(double (*f)(double),
		   double range_x_min,
		   double range_x_max,
		   double range_y_min,
		   double range_y_max){

	/*clear the graph using while as background*/
	fg_clear_graph(g, (char)0xFF);
	
	/*draw grid in graph using gray color*/
	double iter = (range_y_max - range_y_min)/20;
	fg_draw_grid_y(g, range_y_min, range_y_max, iter, (char)0xAA);
	iter = (range_x_max - range_x_min)/20;
	fg_draw_grid_x(g, range_x_min, range_x_max,  iter, (char)0xAA);

	/*craete X axes using black color*/ 
	fg_create_y(g, range_y_min, range_y_max, 0, (char)0x00);

	/*craete Y axes using black color*/ 
	fg_create_x(g, range_x_min, range_x_max, 0, (char)0x00);

	/*draw graph using black color*/ 
	fg_draw_graph(g, (*f), 
			 range_x_min, range_x_max, range_y_min, range_y_max, (char)0x00);
	fg_write_bitmap(g, "a.bmp");
}
void b1(){

	int x_max = atoi(gtk_entry_get_text(GTK_ENTRY(text_x_max)));
	int x_min = atoi(gtk_entry_get_text(GTK_ENTRY(text_x_min)));
	int y_max = atoi(gtk_entry_get_text(GTK_ENTRY(text_y_max)));
	int y_min = atoi(gtk_entry_get_text(GTK_ENTRY(text_y_min)));

	re_draw(func1, x_min, x_max, y_min, y_max);
	gtk_image_set_from_file(GTK_IMAGE(image_headder), "a.bmp");
}
void b2(){
	int x_max = atoi(gtk_entry_get_text(GTK_ENTRY(text_x_max)));
	int x_min = atoi(gtk_entry_get_text(GTK_ENTRY(text_x_min)));
	int y_max = atoi(gtk_entry_get_text(GTK_ENTRY(text_y_max)));
	int y_min = atoi(gtk_entry_get_text(GTK_ENTRY(text_y_min)));

	re_draw(func2, x_min, x_max, y_min, y_max);
	
	gtk_image_set_from_file(GTK_IMAGE(image_headder), "a.bmp");
	gtk_widget_show(image_headder);
}
void b3(){
	int x_max = atoi(gtk_entry_get_text(GTK_ENTRY(text_x_max)));
	int x_min = atoi(gtk_entry_get_text(GTK_ENTRY(text_x_min)));
	int y_max = atoi(gtk_entry_get_text(GTK_ENTRY(text_y_max)));
	int y_min = atoi(gtk_entry_get_text(GTK_ENTRY(text_y_min)));
	re_draw(func3, x_min, x_max, y_min, y_max);
	
	gtk_image_set_from_file(GTK_IMAGE(image_headder), "a.bmp");
	gtk_widget_show(image_headder);
}
void b4(){
	int x_max = atoi(gtk_entry_get_text(GTK_ENTRY(text_x_max)));
	int x_min = atoi(gtk_entry_get_text(GTK_ENTRY(text_x_min)));
	int y_max = atoi(gtk_entry_get_text(GTK_ENTRY(text_y_max)));
	int y_min = atoi(gtk_entry_get_text(GTK_ENTRY(text_y_min)));
	re_draw(func4, x_min, x_max, y_min, y_max);
	
	gtk_image_set_from_file(GTK_IMAGE(image_headder), "a.bmp");
	gtk_widget_show(image_headder);
}
void b5(){
	int x_max = atoi(gtk_entry_get_text(GTK_ENTRY(text_x_max)));
	int x_min = atoi(gtk_entry_get_text(GTK_ENTRY(text_x_min)));
	int y_max = atoi(gtk_entry_get_text(GTK_ENTRY(text_y_max)));
	int y_min = atoi(gtk_entry_get_text(GTK_ENTRY(text_y_min)));
	re_draw(func5, x_min, x_max, y_min, y_max);
	
	gtk_image_set_from_file(GTK_IMAGE(image_headder), "a.bmp");
	gtk_widget_show(image_headder);
}
void b6(){
	int x_max = atoi(gtk_entry_get_text(GTK_ENTRY(text_x_max)));
	int x_min = atoi(gtk_entry_get_text(GTK_ENTRY(text_x_min)));
	int y_max = atoi(gtk_entry_get_text(GTK_ENTRY(text_y_max)));
	int y_min = atoi(gtk_entry_get_text(GTK_ENTRY(text_y_min)));

	re_draw(func6, x_min, x_max, y_min, y_max);
	
	gtk_image_set_from_file(GTK_IMAGE(image_headder), "a.bmp");
	gtk_widget_show(image_headder);
}
int main(int argc, char **argv){

	g = fg_init(1000, 500);
	fg_clear_graph(g, (char)0xFF);
	fg_write_bitmap(g, "a.bmp");

	GtkWidget *box_buttons;
	GtkWidget *box_text;

	GtkWidget* label_x_min;
	GtkWidget* label_x_max;
	GtkWidget* label_y_min;
	GtkWidget* label_y_max;

	GtkWidget* button_new;
	GtkWidget* button_rem;
	GtkWidget* button_sin;
	GtkWidget* button_tan;
	GtkWidget* button_log;
	GtkWidget* button_cos;

	gtk_init(&argc, &argv);
	window_main = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	
	box_main = gtk_vbox_new (FALSE, 0);
	box_buttons = gtk_hbox_new (FALSE, 0);
	box_text = gtk_hbox_new (FALSE, 0);	

	image_headder = gtk_image_new_from_file ("a.bmp");
	gtk_box_pack_start(GTK_BOX (box_main), image_headder, FALSE, TRUE, 5);

	text_x_max = gtk_entry_new ();
	text_x_min = gtk_entry_new ();
	text_y_max = gtk_entry_new ();
	text_y_min = gtk_entry_new ();

	label_x_min = gtk_label_new("min x");
	label_x_max = gtk_label_new("max x");
	label_y_min = gtk_label_new("min y");
	label_y_max = gtk_label_new("max y");

	gtk_box_pack_start (GTK_BOX (box_text), label_x_min, TRUE, FALSE, 5);
	gtk_box_pack_start (GTK_BOX (box_text), text_x_min, TRUE, FALSE, 5);
	gtk_box_pack_start (GTK_BOX (box_text), label_x_max, TRUE, FALSE, 5);
	gtk_box_pack_start (GTK_BOX (box_text), text_x_max, TRUE, FALSE, 5);
	gtk_box_pack_start (GTK_BOX (box_text), label_y_min, TRUE, FALSE, 5);
	gtk_box_pack_start (GTK_BOX (box_text), text_y_min, TRUE, FALSE, 5);
	gtk_box_pack_start (GTK_BOX (box_text), label_y_max, TRUE, FALSE, 5);
	gtk_box_pack_start (GTK_BOX (box_text), text_y_max, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX (box_main), box_text, FALSE, TRUE, 5);


	button_new = gtk_button_new_with_label ("(x - 1)(x - 2)(x - 3)(x - 4)");
	button_rem = gtk_button_new_with_label ("x*x*x + 3*x*x + 4");
	button_sin = gtk_button_new_with_label ("sin");
	button_tan = gtk_button_new_with_label ("tan");
	button_log = gtk_button_new_with_label ("log");
	button_cos = gtk_button_new_with_label ("cos");
	
	gtk_signal_connect (GTK_OBJECT (button_new), "clicked",
					GTK_SIGNAL_FUNC (b1), NULL);
	gtk_box_pack_start (GTK_BOX (box_buttons), button_new, TRUE, FALSE, 5);
	gtk_widget_show (button_new);
	
	gtk_signal_connect (GTK_OBJECT (button_rem), "clicked",
					GTK_SIGNAL_FUNC (b2), NULL);
	gtk_box_pack_start (GTK_BOX (box_buttons), button_rem, TRUE, FALSE, 5);
	gtk_widget_show (button_rem);
	
	gtk_signal_connect (GTK_OBJECT (button_sin), "clicked",
					GTK_SIGNAL_FUNC (b3), NULL);
	gtk_box_pack_start (GTK_BOX (box_buttons), button_sin, TRUE, FALSE, 5);
	gtk_widget_show (button_sin);
	
	gtk_signal_connect (GTK_OBJECT (button_log), "clicked",
					GTK_SIGNAL_FUNC (b4), NULL);
	gtk_box_pack_start (GTK_BOX (box_buttons), button_log, TRUE, FALSE, 5);
	gtk_widget_show (button_log);
	
	gtk_signal_connect (GTK_OBJECT (button_cos), "clicked",
					GTK_SIGNAL_FUNC (b5), NULL);
	gtk_box_pack_start (GTK_BOX (box_buttons), button_cos, TRUE, FALSE, 5);
	gtk_widget_show (button_cos);
	
	
	gtk_signal_connect (GTK_OBJECT (button_tan), "clicked",
					GTK_SIGNAL_FUNC (b6), NULL);
	gtk_box_pack_start (GTK_BOX (box_buttons), button_tan, TRUE, FALSE, 5);
	gtk_widget_show (button_tan);
	
	gtk_box_pack_start(GTK_BOX (box_main), box_buttons, FALSE, TRUE, 5);
	gtk_container_add(GTK_CONTAINER (window_main), box_main);
	gtk_widget_show(image_headder);
	gtk_widget_show(text_x_max);
	gtk_widget_show(text_x_min);
	gtk_widget_show(text_y_max);
	gtk_widget_show(text_y_min);
	gtk_widget_show(label_x_max);
	gtk_widget_show(label_x_min);
	gtk_widget_show(label_y_max);
	gtk_widget_show(label_y_min);
	gtk_widget_show(box_text);
	gtk_widget_show(image_headder);
	gtk_widget_show(box_main);
	gtk_widget_show(box_buttons);
	gtk_widget_show(window_main);
	gtk_main();
	return 0;
}