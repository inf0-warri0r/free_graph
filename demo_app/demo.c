/*
* Author :Tharindra Galahena
* Project:free_graph - fg_graph drawing library for c/c++ (linux) - demo app
* Date   :28/06/2012
*
*
* 
* 
*     Copyright 2012 Tharindra Galahena
*
* This file is part of free_graph.
*
* free_graph is free software: you can redistribute it and/or modify it under the terms of 
* the GNU General Public License as published by the Free Software Foundation, either 
* version 3 of the License, or any later version. free_graph is distributed in the hope 
* that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General 
* Public License for more details.
*
* You should have received a copy of the GNU General Public License along with free_graph. 
* If not, see http://www.gnu.org/licenses/.
* 
*/

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>
#include <glib.h>

#include <fg_error.h>
#include <fg_structs.h>
#include <free_graph.h>

fg_graph *g;

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


	fg_area out;
	out.x_min = range_x_min;
	out.x_max = range_x_max;
	out.y_min = range_y_min;
	out.y_max = range_y_max;

	fg_area in;
	in.x_min = range_x_min + (1.0/3.0) * (range_x_max - range_x_min);
	in.x_max = range_x_max - (1.0/3.0) * (range_x_max - range_x_min);
	in.y_min = range_y_min + (1.0/3.0) * (range_y_max - range_y_min);
	in.y_max = range_y_max - (1.0/3.0) * (range_y_max - range_y_min);
	
	fg_range range_x;
	range_x.min = range_x_min;
	range_x.max = range_x_max;
	
	fg_range range_y;
	range_y.min = range_y_min;
	range_y.max = range_y_max;
	
	/*white colour*/
	fg_color c_a;
	c_a.R = 0xFF;
	c_a.B = 0xFF;
	c_a.G = 0xFF;
	
	/*gray colour*/
	fg_color c_b;
	c_b.R = 0xAA;
	c_b.B = 0xAA;
	c_b.G = 0xAA;
	
	/*blue color*/
	fg_color c_c;
	c_c.R = 0x00;
	c_c.B = 0xFF;
	c_c.G = 0x00;
	
	/*red colour*/
	fg_color c_d;
	c_d.R = 0xFF;
	c_d.B = 0x00;
	c_d.G = 0x00;
	
	/*clear the graph using while as background*/
	fg_clear_graph(g, c_a);
	
	/*draw grid in graph using gray color*/
	double iter = (range_y_max - range_y_min)/20;
	fg_draw_grid_y(g, &range_y, iter, c_b);
	iter = (range_x_max - range_x_min)/20;
	fg_draw_grid_x(g, &range_x,  iter, c_b);

	/*craete X axes using black color*/ 
	fg_create_y(g, &range_y, 0, c_c);

	/*craete Y axes using black color*/ 
	fg_create_x(g, &range_x, 0, c_c);

	/*draw graph using black color*/ 
	int err;
	if((err = fg_draw_graph(g, (*f), &out, c_c)) <= 0);
		fg_perror("ERROR", err);
	if((err = fg_draw_graph_2(g, (*f), &out, &in, c_d)) <= 0);
		fg_perror("ERROR", err);
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
void close_all(){
	fg_free(g);
	exit(0);
}
int main(int argc, char **argv){

	g = fg_init(1000, 500);
	fg_color c_a;
	c_a.R = 0xFF;
	c_a.B = 0xFF;
	c_a.G = 0xFF;
	fg_clear_graph(g, c_a);
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
	g_signal_connect (window_main, "delete_event", G_CALLBACK (close_all), NULL);

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
