#include "MainGame.h"

void fatalError( std::string error_string )
{
    std::cout << error_string << std::endl;
    std::cout << "Enter any key to quit...";

    int tmp;
    std::cin >> tmp;
    SDL_Quit();
    exit( -1 );
}

MainGame::MainGame()
{
    _window = NULL;
    _screen_width = 1024;
    _screen_height = 768;
    _currentGameState = GameState::PLAY;
}


MainGame::~MainGame()
{
}


void MainGame::run()
{
    initSystems();
    gameLoop();
}

void MainGame::initSystems()
{
    // Init SDL (derp)
    SDL_Init( SDL_INIT_EVERYTHING );

    _window = SDL_CreateWindow( "Game Engine",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        _screen_width, _screen_height,
        SDL_WINDOW_OPENGL );

    if ( _window == NULL ) {
        fatalError( "Could not create SDL window" );
    }

    SDL_GLContext context = SDL_GL_CreateContext( _window );
    if ( context == NULL ) {
        fatalError( "Could not acquire GL context" );
    }

    GLenum error = glewInit();
    if ( error != GLEW_OK ) {
        fatalError( "GLEW init failed: " + error );
    }

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    glClearColor( 1.0f, 0, 1.0f, 1.0f );
}

void MainGame::gameLoop()
{
    while ( _currentGameState != GameState::EXIT ) {
        processInput();
        drawGame();
    }
}

void MainGame::processInput()
{
    SDL_Event  event;

    while ( SDL_PollEvent( &event ) ) {
        switch ( event.type ) {
            case SDL_QUIT:
                _currentGameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                //std::cout << ( _screen_width / event.motion.x ) << ", " << (event.motion.y / _screen_height) << "\n";
                break;
        }
    }
}

void MainGame::drawGame()
{
    glClearDepth( 1.0 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glEnableClientState( GL_COLOR_ARRAY );
    glBegin( GL_TRIANGLES );

    glColor3f( 1, 0.8, 0 );
    glVertex2f( 0, 0 );
    glVertex2f( 0, 500 );
    glVertex2f( 500, 500 );


    glEnd();

    SDL_GL_SwapWindow( _window );
}
