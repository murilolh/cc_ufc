varying vec3 normal;
varying vec3 sup;

void main(void)
{
	// Obtém a posição do vértice em coordenadas de câmera
	sup = vec3(gl_ModelViewMatrix * gl_Vertex);

	// E a normal, também em coordenadas de câmera
	normal = gl_NormalMatrix * gl_Normal;

	// Calcula posição do vértice
	// (equivalente a gl_ModelViewProjectionMatrix * gl_Vertex)
	gl_Position = ftransform(); 
}

