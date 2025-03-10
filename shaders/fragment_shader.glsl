#version 460 core

out vec4 FragColor;


in vec3 vertexColor;
in vec2 TexCoord;


uniform sampler2D texture1;
uniform sampler2D texture2;

void main(){

   //  FragColor = texture(ourTexture, TexCoord);
   // FragColor = texture(texture1, TexCoord) * vec4(vertexColor, 1.0);  
   FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);

};
