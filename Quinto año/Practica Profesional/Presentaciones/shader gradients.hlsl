//Test colores y gradientes
//-----------------------------------------------------------------
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // Normalized pixel coordinates (from 0 to 1)
    //vec2 uv = fragCoord/iResolution.xy;
    // Output to screen
    //fragColor = vec4(uv.y,uv.x,sin(5.0*iTime),1.0);//
    fragColor=vec4(0.0,0.0,0.0,1.0);
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = fragCoord/iResolution.xy;
    // Output to screen
    fragColor = vec4(uv.y,uv.x,iMouse.x/iResolution.x,1.0);//
    //fragColor=vec4(0.0,0.0,0.0,1.0);
}


//Daltonizmo.fx
//------------------------------------------------------------------
#define NINGUNO 0
#define PROTANOPIA 1
#define DEUTERANOPIA 2
#define TRITANOPIA 3

const int daltonismo=PROTANOPIA;


void Daltonize( out vec4 myoutput, in vec4 myinput )
{
	// matriz de conversion RGB a LMS
	float L = (17.8824f * myinput.r) + (43.5161f * myinput.g) + (4.11935f * myinput.b);
	float M = (3.45565f * myinput.r) + (27.1554f * myinput.g) + (3.86714f * myinput.b);
	float S = (0.0299566f * myinput.r) + (0.184309f * myinput.g) + (1.46709f * myinput.b);
    
    float l;
    float m;
    float s;
    
    // Simulamos los efectos del daltonismo
    
	if ( daltonismo == PROTANOPIA) // Protanopia - los rojos son reducidos
    {
        l = 0.0f * L + 2.02344f * M + -2.52581f * S;
        m = 0.0f * L + 1.0f * M + 0.0f * S;
        s = 0.0f * L + 0.0f * M + 1.0f * S;
    }    
	else if ( daltonismo == DEUTERANOPIA) // Deuteranopia - los verdes son reducidos
    {
        l = 1.0f * L + 0.0f * M + 0.0f * S;
        m = 0.494207f * L + 0.0f * M + 1.24827f * S;
        s = 0.0f * L + 0.0f * M + 1.0f * S;
    }
    
	else if ( daltonismo == TRITANOPIA) // Tritanope - los azules son reducidos
    {
        l = 1.0f * L + 0.0f * M + 0.0f * S;
        m = 0.0f * L + 1.0f * M + 0.0f * S;
        s = -0.395913f * L + 0.801109f * M + 0.0f * S;
    }
    else
    {
        myoutput = myinput;
        return;
    }
    
	// matriz de conversion LMS a RGB
	vec4 error;
	error.r = (0.0809444479f * l) + (-0.130504409f * m) + (0.116721066f * s);
	error.g = (-0.0102485335f * l) + (0.0540193266f * m) + (-0.113614708f * s);
	error.b = (-0.000365296938f * l) + (-0.00412161469f * m) + (0.693511405f * s);
	error.a = 1.0;
	
    // Isolamos los valores de colores que son invisibles para las personas con el daltonismo seleccionado
	error = (myinput - error);
    //myoutput=error;
    //return;
    
	
    // Desplazamos los colores al espectro visible (aplicando modificaciones de error)
    vec4 correction;
	correction.r = 0.0;
	correction.g = (error.r * 0.7) + (error.g * 1.0);
	correction.b = (error.r * 0.7) + (error.b * 1.0);
	
    // Agregamos la compensacion a los valores originales
    correction = myinput + correction;
    correction.a = myinput.a;
	
	myoutput = correction;
}


void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 xy = fragCoord.xy / iResolution.xy;
    vec4 texColor = texture(iChannel0,xy); // Obtenemos el pixel de la textura
    Daltonize(fragColor, texColor);
}