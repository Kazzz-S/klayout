// [1]
#version 150

in vec4 posAttr;

void main() {
   gl_Position = posAttr;
};
----------------------------------------------------------------------------------------------------
#version 120

attribute vec4 posAttr;

void main() {
   gl_Position = posAttr;
}


====================================================================================================
// [2]
#version 150

uniform vec4 color;
uniform vec4 ambient;
uniform vec3 illum;
out lowp vec4 vertexColor;
uniform mat4 matrix;
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

void main() {
   vec4 p0 = gl_in[0].gl_Position;
   vec4 p1 = gl_in[1].gl_Position;
   vec4 p2 = gl_in[2].gl_Position;
   vec3 n = cross(p2.xyz - p0.xyz, p1.xyz - p0.xyz);
   float dp = dot(normalize(n), illum);
   vertexColor = color * (dp * 0.5 + 0.5) - (min(0.0, dp) * ambient);
   vertexColor.a = 1.0;
   gl_Position = matrix * p0;
   EmitVertex();
   gl_Position = matrix * p1;
   EmitVertex();
   gl_Position = matrix * p2;
   EmitVertex();
   EndPrimitive();
};
----------------------------------------------------------------------------------------------------
#version 120

uniform vec4 color;
uniform vec4 ambient;
uniform vec3 illum;
uniform mat4 matrix;
varying vec4 vertexColor;

void main() {
   vec4 p0 = gl_PositionIn[0];
   vec4 p1 = gl_PositionIn[1];
   vec4 p2 = gl_PositionIn[2];
   vec3 n = cross(p2.xyz - p0.xyz, p1.xyz - p0.xyz);
   float dp = dot(normalize(n), illum);
   vertexColor = color * (dp * 0.5 + 0.5) - (min(0.0, dp) * ambient);
   vertexColor.a = 1.0;
   gl_Position = matrix * p0;
   EmitVertex();
   gl_Position = matrix * p1;
   EmitVertex();
   gl_Position = matrix * p2;
   EmitVertex();
   EndPrimitive();
}

====================================================================================================
// [3]
#version 150

in lowp vec4 vertexColor;
out lowp vec4 fragColor;
uniform highp float mist_factor;
uniform highp float mist_add;

lowp vec4 color_by_z(lowp vec4 c, highp float z) {
  highp float mist_rgb = c.g * mist_factor + mist_add;
  lowp vec4 mist_color = vec4(mist_rgb, mist_rgb, mist_rgb, 1.0);
  highp float d = 0.12; //  d + dd/2 = 0.15 = 1/?
  highp float dd = 0.06;
  highp float f = 1.0;
  if (z < d - dd) {
    f = 0.0;
  } else if (z < d + dd) {
    f = (z - (d - dd)) / (2.0 * dd);
  }
  return (1.0 - f) * mist_color + f * c;
};

void main() {
   fragColor = color_by_z(vertexColor, gl_FragCoord.w);
};
----------------------------------------------------------------------------------------------------
#version 120

varying vec4 vertexColor;
varying vec4 fragColor;
uniform float mist_factor;
uniform float mist_add;

vec4 color_by_z(vec4 c, float z) {
    float mist_rgb = c.g * mist_factor + mist_add;
    vec4 mist_color = vec4(mist_rgb, mist_rgb, mist_rgb, 1.0);
    float d = 0.12;
    float dd = 0.06;
    float f = 1.0;
    if (z < d - dd) {
        f = 0.0;
    } else if (z < d + dd) {
        f = (z - (d - dd)) / (2.0 * dd);
    }
    return (1.0 - f) * mist_color + f * c;
}

void main() {
   fragColor = color_by_z(vertexColor, gl_FragCoord.w);
}


====================================================================================================
// [4]
#version 150

in vec4 posAttr;
uniform mat4 matrix;

void main() {
   gl_Position = matrix * posAttr;
};
----------------------------------------------------------------------------------------------------
#version 120

attribute vec4 posAttr;
uniform mat4 matrix;

void main() {
   gl_Position = matrix * posAttr;
}


====================================================================================================
// [5]
#version 150

uniform lowp vec4 color;
out lowp vec4 fragColor;
uniform highp float mist_factor;
uniform highp float mist_add;

lowp vec4 color_by_z(lowp vec4 c, highp float z) {
  highp float mist_rgb = c.g * mist_factor + mist_add;
  lowp vec4 mist_color = vec4(mist_rgb, mist_rgb, mist_rgb, 1.0);
  highp float d = 0.12; //  d + dd/2 = 0.15 = 1/?
  highp float dd = 0.06;
  highp float f = 1.0;
  if (z < d - dd) {
    f = 0.0;
  } else if (z < d + dd) {
    f = (z - (d - dd)) / (2.0 * dd);
  }
  return (1.0 - f) * mist_color + f * c;
};

void main() {
   fragColor = color_by_z(color, gl_FragCoord.w);
};
----------------------------------------------------------------------------------------------------
#version 120

uniform vec4 color;
varying vec4 fragColor;
uniform float mist_factor;
uniform float mist_add;

vec4 color_by_z(vec4 c, float z) {
    float mist_rgb = c.g * mist_factor + mist_add;
    vec4 mist_color = vec4(mist_rgb, mist_rgb, mist_rgb, 1.0);
    float d = 0.12;
    float dd = 0.06;
    float f = 1.0;
    if (z < d - dd) {
        f = 0.0;
    } else if (z < d + dd) {
        f = (z - (d - dd)) / (2.0 * dd);
    }
    return (1.0 - f) * mist_color + f * c;
}

void main() {
   fragColor = color_by_z(color, gl_FragCoord.w);
}


====================================================================================================
// [6]
#version 150

in vec4 posAttr;
uniform mat4 matrix;

void main() {
   gl_Position = matrix * posAttr;
};
----------------------------------------------------------------------------------------------------
#version 120

attribute vec4 posAttr;
uniform mat4 matrix;

void main() {
   gl_Position = matrix * posAttr;
}


====================================================================================================
// [7]
#version 150

uniform lowp vec4 color;
out lowp vec4 fragColor;
void main() {
   fragColor = color;
};
----------------------------------------------------------------------------------------------------
#version 120

uniform vec4 color;
varying vec4 fragColor;

void main() {
   fragColor = color;
}
====================================================================================================
