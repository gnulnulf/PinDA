 //solenoids.h
#ifndef SOLENOIDS_h
#define SOLENOIDS_h
 
 #include "pinda.h"
 #include "mc6821.h"
 /*enum sol_nr { 
	PIA_PA0=0,PIA_PA1,PIA_PA2,PIA_PA3,PIA_PA4,PIA_PA5,PIA_PA6,PIA_PA7,
	PIA_PB0=8,PIA_PB1,PIA_PB2,PIA_PB3,PIA_PB4,PIA_PB5,PIA_PB6,PIA_PB7,
	PIA_CA1=17,PIA_CA2=18,
	PIA_CB1=19,PIA_CB2=20
	};
 */
 enum solenoid_type { SOLENOID_UNUSED, SOLENOID_PULSE,SOLENOID_CONT }; 
  
 class LATCH8 {
	public:
		LATCH8( CPUBUSClass * _bus, unsigned int address, String _name="LATCH");
		void on( uint8_t bit);
		void off( uint8_t bit);
		void toggle( uint8_t bit);
		void all(uint8_t data);
		bool isOn(uint8_t bit);
		
	private:
		CPUBUSClass * bus;
		uint8_t state;
		String name;
		unsigned int address;
}; 
  
 class SOLENOID : public PindaObj {
	protected:
 		uint8_t timer;
 	
		bool active;
		bool state;
		String name;
		solenoid_type type;
		uint8_t max_on;
		uint8_t min_off;

		uint16_t delay_timer;
		uint8_t off_timer;
		
		
	public:
		SOLENOID ( void );
		void test(void);
		//String getName(void);
		//void on(void);
		void off( void);
		//void toggle(void);
		//bool isOn(void);
		void serviceTimer(void);
 };

 
 
class SOLENOID_demo : public SOLENOID {
//		uint8_t timer;
	public:
		SOLENOID_demo( 
			uint8_t _port,
			bool _active=true,
			solenoid_type _type=SOLENOID_PULSE,
			uint8_t _max_on=10,
			uint8_t _min_off=10,
			String _name="SOLENOIDDEMO"
		);
		void on(void);
		void off(void);
		void toggle(void);
		bool isOn(void);
				void serviceTimer(void);
	//private:
		uint8_t port;
//		String name;
//		solenoid_type type;
//		uint8_t max_on;
//		bool active;
//		bool state;

};

 
 
class SOLENOID_latch : public SOLENOID {
	public:
		SOLENOID_latch( 
			LATCH8 * _latch, 
			uint8_t _bit,
			bool _active,
			solenoid_type _type=SOLENOID_UNUSED,
			uint8_t _max_on=10,
			uint8_t _min_off=10,
			String _name="SOLENOIDLATCH"
		);
		void on(void);
		void off(void);
		void toggle(void);
		bool isOn(void);
		void serviceTimer(void);
	private:
		LATCH8 * latch;
		uint8_t bitnr;

//		String name;
//		solenoid_type type;
//		uint8_t max_on;
//		bool active;
	//	bool state;
//		uint8_t timer;

};

class SOLENOID_pia : public SOLENOID {
	public:
		SOLENOID_pia( 
			MC6821 * _pia,
			pia_io _index,
			bool _active=true,
			solenoid_type _type=SOLENOID_UNUSED,
			uint8_t _max_on=10,
			uint8_t _min_off=10,
			String _name="SOLENOIDPIA"
		);
		void on(void);
		void onDelay(uint16_t delay=0);
		void off(void);
		void toggle(void);
		bool isOn(void);
				void serviceTimer(void);
	
	private:
		MC6821 * pia;
		pia_io index;

		String name;
//		solenoid_type type;
//		uint8_t max_on;
//		bool active;
//		bool state;
//		uint16_t delay_timer;
//		uint8_t off_timer;
//		uint8_t timer;
}; 


#endif //SOLENOIDS