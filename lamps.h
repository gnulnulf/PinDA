#ifndef LAMPS_h
#define LAMPS_h

//typedef FastDelegate0<> FuncDelegate;

//extern MC6821 PIAU54;

class lamps : public PindaObj {
	public:
		lamps(void);
		/**
		* Interrupt is used for timed actions from the pinda interrupt timer
		*/
		virtual void interrupt(void); 
		/*
		* the serviceLoop is for maintenance tasks which are not time critical and should be in the main loop.
		*/
		virtual void serviceLoop(void);
		/**
		* show the current state of the lamps as text
		*/
		void show(void);
		/**
		* turn lamp on
		*
		* @param number lamp index from 0 to 63
		*/
		void on(uint8_t number);
		void off(uint8_t number);
		void toggle(uint8_t number);
		
		void set(uint8_t number,uint8_t state);
		void rowSet( const uint8_t row, const uint8_t data);
		void allSet( uint8_t row1,uint8_t row2,uint8_t row3,uint8_t row4,uint8_t row5,uint8_t row6,uint8_t row7,uint8_t row8);
		void allOff( void);
		void allOn( void);
	//protected:
		uint8_t lampdata[8]; //!< the standard lamp container
		uint8_t currentRow;
};

//typedef void (lamps::* interrupt_ptr)(void);


//lamps_demo

class  lamps_demo : public lamps {
	public:
		lamps_demo(void);
		//void init(void);
		void interrupt(void);
	private:
	

};


/**
Driver class for Williams System 11a

The Williams System 11 lamps are multiplexed by one MC6821.
When no system11a display is used no lamps will light.
Then a blanking interrupt is needed to enable output.
*/
class  lamps_williams11a : public lamps {
	public:
//	method intfunc;
			lamps_williams11a( MC6821 * piaref);
			//void init( MC6821 * piaref);
			void interrupt();
	
		MC6821 * pia;
	private:

		//uint_8 row;

};
//typedef void (lamps_williams11a::* interrupt_williams11a_ptr)(void);



class LAMP {
	public:
	LAMP( lamps * _lampptr , uint8_t index, String name="UNNAMED") ;
		
		void on(void);
		void off(void);
		void toggle(void);
		void setName( String _name);
		String getName( void );
	
	private:
		lamps * lampptr;
		uint8_t index;
		String name;

};



#endif //LAMPS_h