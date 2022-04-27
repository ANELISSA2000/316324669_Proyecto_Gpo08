// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"
// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();


// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
float rot = 0.0;
float active_c = 0.0;
float active_s = 0.0;
bool anim = false;
bool silla = false;
bool cajon = false;
int x = 0;
int y = 0;




int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
  /*  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );*/

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Adaptacion,carga de modelos y camara sintetica", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    // Set the required callback functions
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define the viewport dimensions
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Setup and compile our shaders
    Shader shader("Shaders/modelLoading.vs", "Shaders/modelLoading.frag");

    // Load models
    Model ALIEN((char*)"Models/Alien/alien.obj");
    Model GODDARD((char*)"Models/Goddard/Goddard.obj");
    Model FACHADA((char*)"Models/Casa/Fachada.obj");
    Model CAMA((char*)"Models/Cama/Cama.obj");
    Model ESCRITORIO((char*)"Models/Escritorio_s/Escriotorio_s.obj");
    Model CAJON((char*)"Models/Cajon/Cajon.obj");
    Model SILLA((char*)"Models/Silla/Silla.obj");
    Model MOVIL((char*)"Models/Movil/Movil.obj");
    Model BURO((char*)"Models/Buro/buro.obj");
    Model SILLON((char*)"Models/Sillon/Sillon.obj");
    Model MESA((char*)"Models/Mesa/Mesa.obj");
    Model CUCHARA((char*)"Models/Cuchara/Cuchara.obj");
    Model PUERTA((char*)"Models/Puerta/Puerta.obj");


   
    glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);



    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded model
        glm::mat4 model(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        FACHADA.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(3.428f, 3.245f, -4.611f));
        model = glm::scale(model, glm::vec3(0.284f, 0.284f, 0.284f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ALIEN.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.251f, 3.28f, -3.11f));
        model = glm::scale(model, glm::vec3(0.113f, 0.113f, 0.113f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        GODDARD.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(4.723f, 3.252f, -3.031f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.692f, 0.692f, 0.692f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        CAMA.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.676f, 3.297f, 4.413f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.192f, 0.192f, 0.192f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ESCRITORIO.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.444f, 3.735f, 4.215+active_c));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.192f, 0.192f, 0.192f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        CAJON.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(2.3+active_s, 3.789f, 3.285));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.192f, 0.192f, 0.192f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        SILLA.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.561f, 5.345f, -3.158f));
        model = glm::scale(model, glm::vec3(0.138f, 0.138f, 0.138f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        MOVIL.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(3.451f, 3.361f, -1.405f));
        model = glm::scale(model, glm::vec3(0.417f, 0.417f, 0.417f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        BURO.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.749f, 0.0f, -5.328f));
        model = glm::scale(model, glm::vec3(0.391f, 0.391f, 0.391f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        SILLON.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.772f, 0.141f, -3.933f));
        model = glm::scale(model, glm::vec3(0.297f, 0.297f, 0.297f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        MESA.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.389f, 1.056f, -4.261f));
        model = glm::rotate(model, glm::radians(-58.095f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.166f, 0.166f, 0.166f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        CUCHARA.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-1.068f, 4.37f, 2.76f));
        model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        PUERTA.Draw(shader);

        glBindVertexArray(0);


        // Swap the buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement()
{
    // Camera controls
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }

    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    
    if (anim)////animación de la puerta
    {
      
        if (rot > -46.0f and x == 0) {
            rot -= 0.5f;
           // printf("%f", rot);
            if (rot < -45.0) {
                x = 1;
            }
        }
    }
    if (anim == false) {
        if (rot < 0.5) {
            rot += 0.5f;
            if (rot >= 0) {
                x = 0;
            }
        }
    }

    if (cajon) {
        if (y == 1) {
            active_c += 0.01;
            if (active_c > 0.0) {
                cajon = false;
                y = 0;
            }
        }
        else {
            active_c -= 0.01;
            if (active_c <-0.5) {
                cajon = false;
                y = 1;
            }
        }
    }

    if (silla) {
        if (y == 0) {
            active_s += 0.01;
            if (active_s > 0.0) {
                silla = false;
                y = 1;
            }
        }
        else {
            active_s -= 0.01;
            if (active_s < -1.5) {
                silla = false;
                y = 0;
            }
        }
    }
    

}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }

    if (keys[GLFW_KEY_O] and x == 0)
    {
        anim = true;

    }
    if (keys[GLFW_KEY_O] and x == 1)
    {
        anim = false;

    }

    if (keys[GLFW_KEY_C])
    {
        cajon = !cajon;
    }
    if (keys[GLFW_KEY_Z])
    {
        silla = !silla;
    }

  
    


}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}

