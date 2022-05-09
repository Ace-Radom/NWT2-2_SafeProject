void setup(){
    pinMode( 5 , INPUT );
    pinMode( 6 , INPUT );
    pinMode( 7 , INPUT );
    pinMode( 8 , INPUT );
    pinMode( 9 , INPUT );
    pinMode( 10 , INPUT );
    pinMode( 11 , INPUT );
    Serial.begin( 9600 );
}

void loop(){
    if ( digitalRead( 5 ) == HIGH )
    {
        Serial.print( "5" );
    }
    if ( digitalRead( 6 ) == HIGH )
    {
        Serial.print( "6" );
    }
    if ( digitalRead( 7 ) == HIGH )
    {
        Serial.print( "7" );
    }
    if ( digitalRead( 8 ) == HIGH )
    {
        Serial.print( "8" );
    }
    if ( digitalRead( 9 ) == HIGH )
    {
        Serial.print( "9" );
    }
    if ( digitalRead( 10 ) == HIGH )
    {
        Serial.print( "10" );
    }
    if ( digitalRead( 11 ) == HIGH )
    {
        Serial.print( "11" );
    }
    delay( 100 );
}