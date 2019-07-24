#pragma once

#define DEFAULT_VS																			\
"#version 150 \n"																			\
																							\
"//uniform mat4 projectionMatrix;\n"                                                          \
"//uniform mat4 modelViewMatrix;\n"															\
"attribute vec3 vertexPosition;\n"															\
																							\
"void main()\n"																				\
"{\n"																						\
	"//gl_Position = projectionMatrix * modelViewMatrix * vec4(vertexPosition, 1.0);\n"		\
	"gl_Position = vec4(vertexPosition, 1.0);\n"											\
"}\n"																						
																							
#define DEFAULT_FS																			\
"#version 150 \n"																			\
																							\
"void main()\n"																				\
"{\n"																						\
	"gl_FragColor = vec4(0.0, 1.0, 1.0, 1.0);\n"											\
"}\n"