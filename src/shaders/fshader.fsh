uniform sampler2D qt_Texture0;
varying highp vec4 qt_TexCoord0;
uniform highp vec4 result_color;

void main(void)
{
    gl_FragColor = result_color;
//    gl_FragColor = texture2D(qt_Texture0, qt_TexCoord0.st);
}
