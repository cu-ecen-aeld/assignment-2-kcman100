
#include <stdio.h>
#include <syslog.h>
#include <string.h>

int main( int argc , char *argv[] )
{
  printf("Ken's writer application in C-Code\r\n") ;

  openlog( NULL ,0 , LOG_USER ) ;

  printf("argc = %d\r\n",argc) ;

  for( int index=0 ; index<argc ; index++ )
    printf("  argv[%d] = %s\r\n",index,argv[index]) ;

  #define MAX_FILENAME_LENGTH (256)
  #define MAX_STRING_TO_WRITE_LENGTH (2048)

  char filename[MAX_FILENAME_LENGTH+1]= "" ;
  char string_to_write[MAX_STRING_TO_WRITE_LENGTH] = "" ;

  if( argc < 3 )
  {
    syslog( LOG_ERR , "The required two arguments not provided.  Usage: writer <filename> <string-to-write-to-file>." ) ;
    return 1 ;
  }

  if( strlen( argv[1] ) < MAX_FILENAME_LENGTH )
  {
    strcpy( filename , argv[1] ) ;
  }
  else
  {
    syslog( LOG_ERR , "Filename too long, greater than %u characters" , MAX_FILENAME_LENGTH ) ;
    return 1 ;
  }

  if( strlen( argv[2] ) < MAX_STRING_TO_WRITE_LENGTH )
  {
    strcpy( string_to_write , argv[2] ) ;
  }
  else
  {
    syslog( LOG_ERR , "String to write to file too long, greater than %u characters" , MAX_STRING_TO_WRITE_LENGTH ) ;
    return 1 ;
  }

  syslog( LOG_DEBUG , "Writing %s to %s" , string_to_write , filename ) ;

  FILE *fp = fopen( filename , "w" ) ;

  if( fp == NULL )
  {
    syslog( LOG_ERR , "Cannot create filename %s" , filename ) ;
    return 1 ;
  }

  fprintf( fp , "%s" , string_to_write ) ;

  fclose( fp ) ;

  return 0 ;

}

