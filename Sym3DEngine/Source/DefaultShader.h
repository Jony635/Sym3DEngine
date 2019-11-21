#pragma once

#define DEFAULT_VS																			\
"#version 150 \n"																			\
																							\
"uniform mat4 projectionMatrix;\n"                                                          \
"uniform mat4 modelViewMatrix;\n"															\
"attribute vec3 vertexPosition;\n"															\
"attribute vec2 aTexCoord;\n"																\
																							\
"varying vec2 TexCoord;\n"																	\
																							\
"void main()\n"																				\
"{\n"																						\
	"gl_Position = projectionMatrix * modelViewMatrix * vec4(vertexPosition, 1.0);\n"		\
	"TexCoord = aTexCoord;\n"																\
"}\n"																						
																							
#define DEFAULT_FS																			\
"#version 150 \n"																			\
																							\
"uniform vec4 color;\n"																		\
"uniform sampler2D customTexture;\n"														\
																							\
"varying vec2 TexCoord;\n"																	\
																							\
"void main()\n"																				\
"{\n"																						\
	"gl_FragColor = texture(customTexture, TexCoord) * color;\n"									\
"}\n"