varying vec3 normal;
varying vec3 sup;

void main(void)
{
	// Obt�m a posi��o do v�rtice em coordenadas de c�mera
	sup = vec3(gl_ModelViewMatrix * gl_Vertex);

	// E a normal, tamb�m em coordenadas de c�mera
	normal = gl_NormalMatrix * gl_Normal;

	// Calcula posi��o do v�rtice
	// (equivalente a gl_ModelViewProjectionMatrix * gl_Vertex)
	gl_Position = ftransform(); 
}

