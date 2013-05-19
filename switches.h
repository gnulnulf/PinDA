 #ifndef SWITCHES_h
#define SWITCHES_h



class switches {
	public:
		switches(void);
		/**
		* Interrupt is used for timed actions from the pinda interrupt timer
		*/
		void interrupt(void); 
		/*
		* the serviceLoop is for maintenance tasks which are not time critical and should be in the main loop.
		*/
		void serviceLoop(void);
		void show(void);
		uint8_t getRow( uint8_t row);
		uint8_t get(uint8_t number);
		bool isOn( uint8_t number );
		void rowSet( const uint8_t row, const uint8_t data);
		void allSet( uint8_t row1,uint8_t row2,uint8_t row3,uint8_t row4,uint8_t row5,uint8_t row6,uint8_t row7,uint8_t row8);
		bool flankup( uint8_t number);
		bool flankdown( uint8_t number);
		
		protected:
		uint8_t switchdata[8]; //!< the standard lamp container
		uint8_t switchdatalast[8]; //!< the standard lamp container
		uint8_t currentRow;
		uint8_t flankupdata[8]; 
		uint8_t flankdowndata[8]; 

		
		};

//typedef void (lamps::* interrupt_ptr)(void);


//lamps_demo

class  switches_demo : public switches {
	public:
		void init(void);
		void interrupt(void);
	private:
	#define SW1 41
#define SW2 40
#define SW3 39
#define SW4 38
#define SW5 7
#define SW6 6
#define SW7 5
#define SW8 4

};


//http://stackoverflow.com/questions/8819580/callback-function-pointers-c-with-without-classes

//lamps_williams11a
// blanking is needed for output
class  switches_williams11a : public switches {
	public:
//	method intfunc;
			void init( MC6821 * _pia);
			void interrupt();
	
	
	private:
		MC6821 * pia;
		//uint_8 row;

};
//typedef void (switches_williams11a::* interrupt_williams11a_ptr)(void);

#endif //SWITCHES_h