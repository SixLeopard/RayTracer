#version 460

in vec2 fragTexCoord;
in vec4 fragColor;

uniform vec2 resolution;
uniform vec3 sqaure;

uniform sampler2D datatexture;

out vec4 finalColor;

void main(){
    vec4 color;
    int sqaure_size = 1920;

    for (int i = 0; i < 1920; i++){
        for (int j = 0; j < 1080; j++){
            if ((texture(datatexture, fragTexCoord).x > 0.5)){
                vec2 sqaureNew = vec2(i,j);
                if (gl_FragCoord.x > sqaureNew.x && gl_FragCoord.x < sqaureNew.x + sqaure_size && gl_FragCoord.y > sqaureNew.y && gl_FragCoord.y < sqaureNew.y + sqaure_size){
                    finalColor = vec4(0,0,gl_FragCoord.x/resolution.x,1);
                    return;
                }
                else {
                    finalColor = vec4(1,1,1,1);
                    return;
                }
            }
            else {
                    finalColor = vec4(1,1,1,1);
                    return;
                }
        }
    }

    //if (gl_FragCoord.x > sqaure.x && gl_FragCoord.x < sqaure.x + sqaure.z && gl_FragCoord.y > sqaure.y && gl_FragCoord.y < sqaure.y + sqaure.z){
    //    color = vec4(0,0,gl_FragCoord.x/resolution.x,1);
    //}
    //else {
    //    color = texture(datatexture,fragTexCoord);
        //color = vec4(color.x,color.y,color.z, 1);
        //color = vec4(1,1,1,1);
    //}

    //color = texture(datatexture,fragTexCoord);
    //finalColor = color;
    finalColor = texture(datatexture, fragTexCoord);
}