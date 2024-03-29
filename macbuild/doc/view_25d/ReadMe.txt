This directory contains the intermediate files for modifying
    "src/plugins/tools/view_25d/lay_plugin/layD25ViewWidget.cc" ---(1)

to fix the problem reported by
    https://github.com/KLayout/klayout/issues/941
    https://github.com/KLayout/klayout/issues/1124
    https://www.klayout.de/forum/discussion/2481


In <gl.cpp>
1. Extract the OpenGL-related code (7 blocks of code) from (1).
2. Pass each of them to ChatGPT to downconvert for '#version 120'.

<gl-src.cpp>.
3. Reformat the code for copy and paste.
4. Manually edit (1) with the '#if defined(__WITH_OPENGL_3_2__)' directive.

[EOF]
