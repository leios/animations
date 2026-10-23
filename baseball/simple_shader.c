/*------------simple_shader---------------------------------------------------//
 Purpose: This file is a simple example of a fragment shader with quibble
   Notes: After installation, compile with:
              `gcc -o simple_shader simple_shader.c -lquibble`
//----------------------------------------------------------------------------*/

#include <stdio.h>

#include "quibble.h"

int main(void){

    quibble_program qp = qb_parse_program_file("simple_shader.qbl");
    qb_configure_program(&qp, 0, 0);

    int width = 1920;
    int height = 1080;
    quibble_pixels qpix = 
        qb_create_pixel_array(qp, width, height, RGBA8888);

    float world_size_x = 4;
    float ppu = width / world_size_x;
    float world_size_y = height/ppu;

    float world_position_x = 0;
    float world_position_y = 0;

    quibble_simple_camera qcam = qb_create_simple_camera(ppu,
                                                         world_size_x,
                                                         world_size_y,
                                                         world_position_x,
                                                         world_position_y);

    qb_set_args(&qp, "simple_shader", 2,
                "quibble_pixels_rgba8888 qps", qpix,
                "quibble_simple_camera qcam", &qcam);


    qb_run(qp, "simple_shader", width*height, 256);

    qb_pixels_device_to_host(qpix);
    qb_write_png_file("check.png", qpix);

    qb_free_program(qp);
    qb_free_pixels(qpix);

    return 0;
}
