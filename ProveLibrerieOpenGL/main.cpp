#include "main.h"
#include "Configuration.h"


// il vettore delle dim non � importante sia un vettore. si possono mettere due numeri

int main() {

	Configuration& config = Configuration::getIstance();
	Viewer v = config.getView();
	//Scene scene = Scene("triangolo"); //
	//v.setScene(scene);
	//Material mm;
	v.initFirstTime();
	v.Run("stanza");
}







// glfwSetFramebufferSizeCallback(window, Viewer::framebufferSizeCB); // specifico cosa deve fare quando ho la callback. framebufferSizeCB--> tipo di funzione da definire (in modo statico). all'interno della funzione posso far girare del codice quando si fa il size della window

// il callback sono chiamate alle funzioni durante un flusso di lavoro. serve per dire ad un certo punto fai un'azione che dico io. tipo puntatori a funzione


//typedef void (*GLFWframebuffersizefun) (GLFWwindow*, int, int); // firma della funzione, int int sono le nuovbe dimensioni della finestra


/*
cleanView() { // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glClear.xhtml glClear ---- maschere con operatori bit a bit
	glClearColor(---) // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glClearColor.xhtml glClearColor --> setta il colore che glClear utilizza per pulire le info del colore del frame
	glClear(GL_COLOR_BUFFER_BIT);
}
*/
// glfw crea automaticamente il framebuffer per la finestra con i vari parametri e lo associa alla finestra...in futuro dovremo farlo noi

/*
void Viewer::framebufferSizeCB(GLFWwindow* window, int width, height) {
	if (window != nullptr) {
		// glViewPort(0, 0, width, height) // dice a openGl ??? se non lo mettiamo quando ingrandiamo la finestra non mantiene il colore nella parte "nuova" https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glViewport.xhtml
	}

}
*/
