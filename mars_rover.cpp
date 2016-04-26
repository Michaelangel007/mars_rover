#include <stdio.h>

    const char HEADING[] = "ENWS";
    const int  DIRS = (int) sizeof( HEADING ) - 1; // don't count null at end

    struct Point
    {
        int x, y;
    };

    const Point FORWARD[] = {
         { 1, 0} // E   0
        ,{ 0,+1} // N  90
        ,{-1, 0} // W 180
        ,{ 0,-1} // S 270
    };

// Utility

    // Instead using 360 degrees for heading
    // We use one of the four cardinal directions, E, N, W, S
    int HeadingToFacing( const char heading )
    {
        for( int iDir = 0; iDir < DIRS; iDir++ )
            if( HEADING[ iDir ] == heading )
                return iDir;

        return 0; // Unknown heading edge case not specified how should be handled
    }

    int FacingToHeading( int facing )
    {
        return HEADING[ facing ];
    }

// Class
    struct Rover
    {
        int _x;
        int _y;
        int _facing;

        void Init( int x, int y, char heading )
        {
            _x      = x;
            _y      = y;
            _facing = HeadingToFacing( heading );
        }

        void Move()
        {
            int dx = FORWARD[ _facing ].x;
            int dy = FORWARD[ _facing ].y;
            _x += dx;
            _y += dy;
        }

        void Exec( const char *commands )
        {
            const char *p = commands;
            while( *p )
            {
//printf( "%c ", *p );
                switch( *p )
                {
                    case 'L': _facing++; if( _facing >= DIRS) _facing = 0     ; break; //         Clockwise +angle
                    case 'R': _facing--; if( _facing <  0   ) _facing = DIRS-1; break; // Counter-Clockwise -angle
                    case 'M': Move(); break;
                    default: break;
                }
                p++;
//Dump();
            }
        }

        void Dump()
        {
            printf( "%d %d %c\n", _x, _y, FacingToHeading( _facing ) );
        }
    };

int main()
{
    Rover rover[2];

    char line[ 256 ];

    int w, h;
    fgets( line, sizeof( line ), stdin );
    scanf( line, "%d %d", &w, &h );

    for( int iRover = 0; iRover < 2; iRover++ )
    {
        char init[ 256 ];
        char move[ 256 ];
        const char *p = NULL;

        int  x,y;
        char heading;

        fgets( init, sizeof( init ), stdin );
        fgets( move, sizeof( move ), stdin );
        sscanf( init, "%d %d %c", &x, &y, &heading );

//printf( "move: '%s'\n", move );
//printf( "x = %d   y = %d  heading=%c\n", x, y, heading );
        rover[ iRover ].Init( x, y, heading );
        rover[ iRover ].Exec( move );
        rover[ iRover ].Dump();
    }

    return 0;
}
