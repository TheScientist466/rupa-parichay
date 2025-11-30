#version 330 core

uniform sampler2D tex;
uniform float factor;

uniform vec2 texelSize;
uniform ivec2 sampleRect; 

out vec4 outColor;

void main() {
    vec2 pos = floor(factor * gl_FragCoord.xy / 600.0 + 0.5) / factor;
    pos.y = 1.0 - pos.y;
    vec4 sum = vec4(0.0);
    int samples = 0;
    
    for(int y = -sampleRect.y; y <= sampleRect.y; y++) {
        for(int x = -sampleRect.x; x <= sampleRect.x; x++) {
            vec2 _offset = vec2(float(x), float(y)) * texelSize;
            sum += texture2D(tex, pos + _offset);
            samples++;
        } 
    }

    outColor = sum / samples;
}
