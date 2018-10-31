class Camera{
	public:
		float ax, ay, az;
		float ox, oy, oz;
		float nx, ny, nz;

		void setPosicao(float ox, float oy, float oz);
		void setNormal(float ax, float ay, float az);
		void setDirecao(float nx, float ny, float nz);
		Camera(void);
		Camera(float ox, float oy, float oz, float ax, float ay, float az, float nx, float ny, float nz);		
		
};
