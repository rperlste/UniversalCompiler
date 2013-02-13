/*
 * Author:		Robbie Perlstein
 * Student ID:	101130094
 * Assignment:	UniversalCompiler
 */

#include "Scanner.Depracted.h"
#include <string>


    ScannerDepracted::ScannerDepracted(){
		// initial settings
		nextTokenLoaded = false;
		isEofSym = false;
		nextToken = new Token();
    }

    ScannerDepracted::ScannerDepracted( const char* fileInput ){
		// intial settings
		nextTokenLoaded = false;
		isEofSym = false;
		nextToken = new Token();
		// open new file
		this->fin.open( fileInput );
       
    }

	bool ScannerDepracted::setFileToRead( const char* fileInput ){
		// close fin
		if( fin.is_open() )
			fin.close();
		// reload initial settings
		nextTokenLoaded = false;
		isEofSym = false;
		delete[] nextToken;
		nextToken = new Token();
		// open new file
		this->fin.open( fileInput );
		if( fin )
			return true;
		else
			return false;
	}

    bool ScannerDepracted::isDone(){
        if( this->fin.eof() 
			|| isEofSym )
            return true;
        else
            return false;
    }

	Token ScannerDepracted::getNextToken(){
		if( nextTokenLoaded )
			return *nextToken;
		*nextToken = scan();
		nextTokenLoaded = true;
		return *nextToken;
	}

    Token ScannerDepracted::scan() {

		if( nextTokenLoaded ){
			nextTokenLoaded = false;
			return *nextToken;
		}

        if( fin.eof() ){
			isEofSym = true;
            return Token( EofSym, "");
        }


        while( !fin.eof() ){
			this->fin >> currentChar;
				if( fin.eof() ){
					isEofSym = true;
					return Token( EofSym, "");    
				}
            std::string currentValue = "";
            // Test for ID or keyword
            if( ( currentChar >= 'A' &&  currentChar <='Z' )
                    ||	( currentChar >= 'a' &&  currentChar <= 'z' )){

                currentValue += currentChar;
                

                while(	!fin.eof()
					&& (( this->fin.peek() >= 'A' &&  this->fin.peek() <='Z' )
                        || ( this->fin.peek() >= 'a' &&  this->fin.peek() <= 'z' )
                        || ( this->fin.peek() >= '0' &&  this->fin.peek() <= '9' )
						|| this->fin.peek() == '_')){
							
							this->fin >> currentChar;
                            currentValue += currentChar;
                            
                }

                // Convert value to upper case for easy keyword parsing
                std::string upperCaseValue;
                for( int i = 0; i < currentValue.length(); i ++ )
                    upperCaseValue += toupper( currentValue[i] );

                // Test for keywords
                if( upperCaseValue.compare( TokenKeywords::BEGIN ) == 0 ){
                    return Token( BeginSym );
                    
                } else if( upperCaseValue.compare( TokenKeywords::END ) == 0){
                    return Token( EndSym );
                    
                } else if( upperCaseValue.compare(TokenKeywords::READ ) == 0){
                    return Token( ReadSym );
                    
                } else if( upperCaseValue.compare(TokenKeywords::WRITE ) == 0){
                    return Token( WriteSym );
                    
                }
                // Not keyword, so return Id token
                else {
                    return Token( Id,  currentValue );
                    
                }
            }

            // Test for int literal
            else if( currentChar >= '0' && currentChar <= '9' ){

                currentValue += currentChar;
                

                // Load int
				while( this->fin.peek() >= '0' && this->fin.peek() <= '9' ){
					this->fin >> currentChar;
                    currentValue += currentChar;
				}

				if( !this->fin.eof()
					&& isalnum( this->fin.peek() )){

					while( isalnum( this->fin.peek() ) ){
						this->fin >> currentChar;
						currentValue += currentChar;
					}
					return Token( IllegalToken, currentValue );
				} else {
					return Token( IntLiteral,  currentValue );
				}
               
            }

            // Test for delimiters...
            else if( currentChar == ';' ){
                currentValue = currentChar;
				
                return Token( SemiColon );
                
            }
            else if( currentChar == '(' ){
                currentValue = currentChar;
				
                return Token( LParen );
                
            }
            else if( currentChar == ')' ){
                currentValue = currentChar;
				
                return Token( RParen );
                
            }
            else if( currentChar == ','){
                currentValue = currentChar;
				
                return Token( Comma );
                
            }
            else if( currentChar == '+' ){
                currentValue = currentChar;
                return Token( PlusOp );
                
            }
			else if( currentChar == '=' ){
                currentValue = currentChar;
                return Token( EqualOp );
                
            }
			else if( currentChar == '*' ){
                currentValue = currentChar;

				if( this->fin.peek() == '*' ){
					this->fin >> currentChar;
					currentValue += currentChar;
					return Token( ExponentialOp,  currentValue );
				}
                return Token( MultOp,  currentValue );
            }
			else if( currentChar == ':' ){
				currentValue += currentChar;
				if( this->fin.peek() == '=' ) {
					this->fin >> currentChar;
					currentValue += currentChar;
					
					return Token( AssignOp,  currentValue );
					
				} else {
					return Token( Colon,  currentValue );
				}
                
			}
			else if( currentChar == '-' || currentChar == '—' ){
                // Check for comment
                if( this->fin.peek() == '-' || this->fin.peek() == '—' ){
                    while( this->fin.peek() != '\n' && !this->fin.eof()){
						this->fin >> currentChar;
                    }
                }
                // Not comment, is minusOp
                else {
                    currentValue = currentChar;
					
                    return Token( MinusOp,  currentValue );
                    
                }
            }
			else if( currentChar == '$' ){
				return Token( EofSym, "");
			}
			else if( currentChar != ' ' ){
				currentValue = currentChar;
				return Token( IllegalToken, currentValue );
			}
        }
		return Token( IllegalToken );
    }




