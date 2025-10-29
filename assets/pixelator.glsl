#version 330 core

uniform sampler2D tex;
uniform float factor;
out vec4 outColor;

void main() {
    vec2 pos = floor(factor * gl_FragCoord.xy / 600.0 + 0.5) / factor;
    vec4 pixel = texture2D(tex, vec2(pos.x, 1.0 - pos.y));
    outColor = pixel;
}
