#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "rom_engine.h"
#include "models.h"
#include "textures.h"
#include <stdio.h>



int main(int argc, char **argv){

        float backgroundColor[4] = {0.0f, 0.4f, 0.33f, 1.0f};
        RomEngine engine = init_context(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE, backgroundColor, false);
        engine.shadersInitialized = init_shaders(&engine.shader, SHADERS_PATH, FRAGMENT_PATH);
        if(!engine.shadersInitialized){
            perror("Error initializing shaders!");            
        }

        load_texture(&engine, CONTAINER_PATH, 0, false, false);
        load_texture(&engine, SMILEY_PATH, 1, true, true);

        // ! REMOVE FROM HERE.
        engine.shader->use_shader_program(engine.shader->id);
        engine.shader->set_int(engine.shader->id, "texture1", 0);
        engine.shader->set_int(engine.shader->id, "texture2", 1);

        engine.log_engine(&engine);
        draw_triangle(&engine);
        engine.render_loop(&engine);
        engine.release(&engine);
        return 0;
    
}