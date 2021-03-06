const char *skin_vert_src =
"uniform mat4 u_boneMatrices[64];\n"

"layout(location = 0) in vec3 in_pos;\n"
"layout(location = 1) in vec3 in_normal;\n"
"layout(location = 2) in vec4 in_color;\n"
"layout(location = 3) in vec2 in_tex0;\n"
"layout(location = 11) in vec4 in_weights;\n"
"layout(location = 12) in vec4 in_indices;\n"

"out vec4 v_color;\n"
"out vec2 v_tex0;\n"
"out float v_fog;\n"

"void\n"
"main(void)\n"
"{\n"
"	vec3 SkinVertex = vec3(0.0, 0.0, 0.0);\n"
"	vec3 SkinNormal = vec3(0.0, 0.0, 0.0);\n"
"	for(int i = 0; i < 4; i++){\n"
"		SkinVertex += (u_boneMatrices[int(in_indices[i])] * vec4(in_pos, 1.0)).xyz * in_weights[i];\n"
"		SkinNormal += (mat3(u_boneMatrices[int(in_indices[i])]) * in_normal) * in_weights[i];\n"
"	}\n"

"	vec4 Vertex = u_world * vec4(SkinVertex, 1.0);\n"
"	gl_Position = u_proj * u_view * Vertex;\n"
"	vec3 Normal = mat3(u_world) * SkinNormal;\n"

"	v_tex0 = in_tex0;\n"

"	v_color = in_color;\n"
"	v_color.rgb += u_ambLight.rgb*surfAmbient;\n"
"	v_color.rgb += DoDynamicLight(Vertex.xyz, Normal)*surfDiffuse;\n"
"	v_color = clamp(v_color, 0.0, 1.0);\n"
"	v_color *= u_matColor;\n"

"	v_fog = DoFog(gl_Position.z);\n"
"}\n"
;
