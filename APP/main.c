#include"main_config.h"
unsigned char try=0;
unsigned char tot;
unsigned char i=0;
unsigned char motor_steps[2] = {96, 48};
unsigned char key=key_not_pressed;
unsigned char admin_pass[pass_length]="1234";
unsigned char admin_name[max_name_length]="ramy";
unsigned char count_users='0';
uint8 counter=0;
struct User{
 unsigned char username[max_name_length];
 unsigned char userpass[pass_length];
};
struct User users[10]={};
unsigned char user_mode_name[max_name_length];
unsigned char user_mode_pass[pass_length];
unsigned char recieve_name[max_name_length];
unsigned char recieve_pass[pass_length];
unsigned char name_length_count=0;
unsigned char check_admin_name[max_name_length];
unsigned char check_admin_pass[pass_length];
unsigned char choice;
unsigned char user_index='0';
uint8 active_users;
uint8 buffer;
unsigned char digit_1=0;
unsigned char digit_2=0;
unsigned char admin_state=0;
unsigned char user_state=0;
unsigned char user_number='0';
unsigned char data_admin_led=0;
unsigned char data_user_led=0;
double adcA=0.0;
double temperature=0.0;
char tempSTR[10];
uint8 brightness=0;
void menu_admin();
void menu_user();
void add_user();
void remove_user();
void user_menu_data();
void names();
void write_eeprom_pass_admin(unsigned char* pass);
void write_eeprom_name_admin( unsigned char* name);
void admin_init();
void recieve_string(unsigned char* rec_data);
void check(unsigned char* rec_name,unsigned char* rec_pass,unsigned char* checker,unsigned char name_add,unsigned char pass_add,unsigned char eeprom_device_address);
void gate_control();
void fan_off();
void control_leds_admin(unsigned char choose_led);
void clear_led(uint8 choose_leds);
void control_leds_user(unsigned char led_choose);
void init_fast_pwm();
void duty_cycle_update(unsigned int duty_cycle);
void AC_Control();
void Dimmer_Control();
void led_off();
void buzzer();
void PWM_init();
void PWM_set_duty_cycle(uint16_t duty_cycle);
 int main(){
	LCD_Init();
	Keypad_init();
    uart_init_rx(9600);
    uart_init_tx(9600);
    ADC_init();
    i2c_init();
    LCD_Init();
    admin_init();
    while(1){
    	digit_1=0;
    	user_index=0;
 /* count_users='0';

    			write_eeprom(0xA0,users_address_add,count_users);
    		while(count_users<='9'){
    				while(digit_1<4)
    			{
    				write_eeprom(0xA0,name_address_u1+(0x08)*(count_users-48)+digit_1,remove_sign);
    				write_eeprom(0xA0,pass_address_u1+(0x08)*(count_users-48)+digit_1,remove_sign);
    				write_eeprom(0xA0,led_status_u+(0x05)*(count_users-48)+digit_1,remove_sign);
    				users[user_index].username[digit_1]=0;
    				users[user_index].userpass[digit_1]=0;
    				digit_1++;
    			}
    				digit_1=0;
    				while(digit_1<5){
    							write_eeprom(0xA0,led_status_u+(0x05)*(count_users-48)+(digit_1),remove_sign);
    							digit_1++;
    						}
    				count_users++;


    		}

*/
    	names();
    	uart_recie(&key);
        uart_transmit_string("\r\n");
switch(key){
case admin_mode:
	LCD_Clear_Display();
LCD_Send_String_Row_Column(0,0,"admin_mode");
check(recieve_name,recieve_pass,&admin_state,name_address_ad,pass_address_ad,0xA0);
while(admin_state==1)
{
	menu_admin();
	uart_recie(&choice);
	uart_transmit_string("\r\n");
	if(choice=='7')
	{
		key=key_not_pressed;

		 // PWM_set_duty_cycle(key);
		//CLEAR_BIT(DDRD,DDD5);
		//CLEAR_BIT(DDRD,DDD4);
		choice='0';


		//CLEAR_BIT(PORTD,DDD5);
		break;
	}
switch (choice){
	case '1':
	{read_fromEEPROM(&tot,(uint8) 0xA0,users_address_add);
	count_users=tot;
	write_eeprom((uint8) 0xA0,users_address_add,count_users);
	//count_users=0;
	read_fromEEPROM(&count_users,(uint8)0xA0,users_address_add);
	add_user();
		break;
	}
	case '2':
	{
		remove_user();
		break;
	}
	case '3':
	{	LCD_Send_String_Row_Column(0,0,"admin_mode");
	LCD_Send_String_Row_Column(1,0,"door_open");
		gate_control();
		LCD_Clear_Display();
		break;
	}
	case '4':
		//read_fromEEPROM(&data_admin_led,0xA0,led_status_ad);
		//read_fromEEPROM(&data_user_led,0xA0,led_status_u);

	{ if(admin_state==1){
		digit_1=0;

							while(digit_1<6){
						read_fromEEPROM(&data_admin_led,0xA0,led_status_ad+digit_1);
						control_leds_admin(data_admin_led);
						data_admin_led=0;
						digit_1++;

					                 }
		//control_leds_admin(data_admin_led);
	uart_transmit_string("1-open\r\n");
	uart_transmit_string("2-off\r\n");
		uart_recie(&key);
		switch(key){
		case'1':
		{

			uart_transmit_string("enter led 1~5\r\n");
					uart_recie(&key);
					control_leds_admin(key);
					key=key_not_pressed;
					break;
		}
		case'2':
		{

			uart_transmit_string("enter led 1~5\r\n");
			uart_recie(&key);
			clear_led(key);
			key=key_not_pressed;
								break;


		}
		}

	/*	uart_transmit_string("enter led 1~5\r\n");
		uart_recie(&key);
		control_leds_admin(key);
		*/
	}
	else{
		control_leds_user(data_user_led);
		LCD_Send_String_Row_Column(0,0,"enter led 1~5\r\n");
		do{
			key=Keypad_get_pressed_key();
		}while(key==key_not_pressed);
		control_leds_user(key);
	}
		//control_leds_admin(key);
		key=key_not_pressed;
		//control lamps
		break;
	}
	case '5':
	{
		AC_Control();
		//control AC
		break;
	}
	case '6':
	{
		PWM_init();
		Dimmer_Control();
		break;
	}
	default:
		choice='0';
		uart_transmit_string("Please Enter Right Choice\r\n");
		break;
}
}
break;
case user_mode:
	{
	read_fromEEPROM(&tot,0xA0,users_address_add);
count_users=tot;
active_users=count_users;
write_eeprom(0xA0,users_address_add,active_users);
while(active_users>='0'){
	digit_1=0;
	for(digit_1=0;digit_1<4;digit_1++){
		read_fromEEPROM(&buffer,0xA0,name_address_u1+(digit_1)+(0x08)*(active_users-48));
		users[active_users-48].username[digit_1]=buffer;
		buffer=0;
		read_fromEEPROM(&buffer,0xA0,pass_address_u1+(digit_1)+(0x08)*(active_users-48));
		users[active_users-48].userpass[digit_1]=buffer;
		buffer=0;
	}
	active_users--;
}
		user_menu_data();
	}
}
}
}
void check(unsigned char* rec_name,unsigned char* rec_pass,unsigned char* checker,unsigned char name_add,unsigned char pass_add, unsigned char eeprom_device_address){
unsigned char data=0;
unsigned char digit=0;
unsigned char address=0;
unsigned char address_n=0;
unsigned char address_p=0;
unsigned char exist_name=0;
unsigned char exist_pass=0;
address_n=name_add;
while(try<3){
	uart_transmit_string("enter_name\r\n");
	recieve_string(recieve_name);
	_delay_ms(300);
	uart_transmit_string("--------------\r\n");
	_delay_ms(300);
	uart_transmit_string("enter_pin_four_digit\r\n");
	recieve_string(recieve_pass);
	_delay_ms(300);
	uart_transmit_string("--------------\r\n");
	_delay_ms(300);
while(digit<4){
    address=digit;
    read_fromEEPROM(&data,eeprom_device_address,(address+address_n));
    if(data==rec_name[digit]){
        exist_name++;
    }
    digit++;
}
digit=0;
address=0;
address_p=pass_add;
while(digit<4){
    address=digit;
read_fromEEPROM(&data,eeprom_device_address,(address+(address_p)));
    if(data==rec_pass[digit]){
        exist_pass++;
    }
    digit++;
}
if(exist_name==4&&exist_pass==4){
    uart_transmit_string("Successful\r\n");
    *checker=1;
    _delay_ms(1000);
    exist_name=0;
    exist_pass=0;
    digit=0;
    address=0;
    try=0;
    break;
}
 if(exist_name!=4&&exist_pass==4){
    uart_transmit_string("Invalid_Name\r\n");
   uart_transmit_string("Please Enter Right Information\r\n");
    *checker=0;
    exist_name=0;
      exist_pass=0;
      digit=0;
      address=0;
      try++;
    _delay_ms(500);
    continue;
}
if(exist_name==4&&exist_pass!=4){
    uart_transmit_string("Invalid_Pass\r\n");
    uart_transmit_string("Please Enter Right Information\r\n");
    *checker=0;
    exist_name=0;
      exist_pass=0;
      digit=0;
      address=0;
      try++;
    _delay_ms(500);
    continue;
}
if(exist_name!=4&&exist_pass!=4){
    uart_transmit_string("invlaid_name_and_pass\r\n");
    uart_transmit_string("Please Enter Right Information\r\n");
    *checker=0;
    exist_name=0;
      exist_pass=0;
      digit=0;
      address=0;
      try++;
    _delay_ms(500);
    continue;
}
}
if(try>2){
	uart_transmit_string("wait_5sec_for_buzzer\r\n");
	buzzer();
	try=0;
}
}
void menu_admin()
{
	//List that appears in admin mode
	uart_transmit_string("**********\r\n");
	uart_transmit_string("1-Add user\r\n");
	uart_transmit_string("2-Remove user\r\n");
	uart_transmit_string("3-Door Control\r\n");
	uart_transmit_string("4-Lamp Control\r\n");
	uart_transmit_string("5-AC Control\r\n");
	uart_transmit_string("6-Dimming Control\r\n");
	uart_transmit_string("7-Return Home\r\n");
}
void menu_user()
{
	//List that appears in user mode
	LCD_Send_String_Row_Column(0,0,"1-leds");
	LCD_Send_String_Row_Column(0,8,"2-AC");
	LCD_Send_String_Row_Column(1,0,"3-Dimmer");
	LCD_Send_String_Row_Column(1,9,"4-home");
}
void gate_control()
{
	//Setting PORTB Pins as outputs
	DDRB=0xFF;
	LCD_Clear_Display();
	LCD_Send_String_Row_Column(0,0,"Door Opening");
	uart_transmit_string("Door Opening -Wait 5 Seconds\r\n");
	//96 in binary 0b01100000
	//48 in binary 0b00110000
	//  MSB(0110)=MSB(0000) | MSB(0110)
	//PB4 low , PB5 High (90 Degree Rotation)
	PORTB = (PORTB & 0x0F) | (motor_steps[1] & 0b11111111);
	//wait for 5 seconds opening the door
	 _delay_ms(5000);
	// MSB(0011) =MSB(0000) | MSB(0011)
	//PB4 High , PB5 High (Back to Zero)
	 PORTB = (PORTB & 0x0F) | (motor_steps[0] & 0b11111111);
}
void add_user()
{
	//array of size 4 to receive username and userpass and passing them to recieve string function
	uint8 rec_data[4];
	//reading the number of users that already exist from the EEPROM
	read_fromEEPROM(&count_users,0xA0,users_address_add);
	//if count_users equals 9 then we have max number of users entered and we can't add anymore
	if(count_users=='9'+1)
		{
			uart_transmit_string("There is Max Number of users\r\n");
			uart_transmit_string("--------------\r\n");
			admin_state=0;
		}
	else
	{
		unsigned char counts=0;
		unsigned char flag=0;
		char count_users_str[2];
		// Convert the count_users character to a string
		count_users_str[0] = count_users;
		count_users_str[1] = '\0'; // Null-terminate the string
		// Entering the username of the current user
		uart_transmit_string("enter_id_for_user ");
		uart_transmit_string(count_users_str);
		uart_transmit_string("\r\n");
		recieve_string(rec_data);
		uart_transmit_string("\r\n");
		while(counts<9)
		{
			flag=0;
			for(digit_1=0;digit_1<4;digit_1++)
			{
					  if(users[counts].username[digit_1]==rec_data[digit_1])
						{
						  flag++;
						}
					  else
					  {
						  flag=0;
						  break;
					  }
			}
			if(flag==4)
				{
					uart_transmit_string("User Already Existing");
					break;
				}
			counts++;
		}
		if(flag==0)
							{

						//saving the entered username inside the array of struct in username part
						while(digit_1<4)
						{
							users[count_users-48].username[digit_1]=rec_data[digit_1];
							rec_data[digit_1]=0;
							digit_1++;
						}
						digit_1=0;
						//Entering the userpass of the current user
						uart_transmit_string("enter_pin_four_digit_for_user ");
						uart_transmit_string(count_users_str);
						uart_transmit_string("\r\n");
						recieve_string(rec_data);
						uart_transmit_string("\r\n");
						//saving the entered userpass inside the array of struct in userpass part
							while(digit_1<4)
							{
								users[count_users-48].userpass[digit_1]=rec_data[digit_1];
								rec_data[digit_1]=0;
								digit_1++;
							}
							digit_1=0;
							//saving both the userpass ,username which are in the struct array  inside the EEPROM
						while(digit_1<4){
							write_eeprom(0xA0,name_address_u1+(digit_1)+(0x08)*(count_users-48),users[count_users-48].username[digit_1]);
							write_eeprom(0xA0,pass_address_u1+(digit_1)+(0x08)*(count_users-48),users[count_users-48].userpass[digit_1]);
							digit_1++;
						}
						digit_1=0;
						uart_transmit_string("User added Successfully");
						uart_transmit_string("\r\n");
						//incrementing the number of users and saving the new number inside the EEPROM
						count_users++;
						write_eeprom(0xA0,users_address_add,count_users);
						count_users=0x00;
							}

}

}
void names()
{
	//List that appears at start and when choosing return Home
	 uart_transmit_string("1-admin_mode\r\n");
	 uart_transmit_string("2-user_mode\r\n");
}
void write_eeprom_pass_admin(unsigned char* pass){
	//Saving admin pass inside the EEPROM
 	  unsigned char i;
 	 for(i=0;i<pass_length;i++)
 	 {
 		 write_eeprom(0XA0,pass_address_ad+i,pass[i]);
 	 }
  }
void write_eeprom_name_admin( unsigned char* name){
	//Saving admin name inside the EEPROM
	unsigned char j;
	 for(j=0;name[j]!='\0';j++){
		 write_eeprom(0XA0,name_address_ad+j,name[j]);
	 }
}
void admin_init(){
 	 write_eeprom_name_admin(admin_name);
 	 write_eeprom_pass_admin(admin_pass);
}
void recieve_string(unsigned char* rec_data){
	 int i=0;
	 unsigned char recieve_digit=key_not_pressed;
	 for(i=0;(i<max_name_length);i++){
	 	uart_recie(&recieve_digit);
	 	if(recieve_digit==0x0D){
	 		 		break;}
	 	name_length_count++;
	 	rec_data[i]=recieve_digit;
	 	recieve_digit=key_not_pressed;}
}
void remove_user()
{
	read_fromEEPROM(&count_users,0xA0,users_address_add);
	if(count_users=='0')
	{
		uart_transmit_string("No users to Remove\r\n");
		//count_users=0x00;
		write_eeprom(0xA0,users_address_add,count_users);
	}
	//uart_transmit_string("Enter index of User\r\n");
		//	uart_recie(&user_index);

	else
	{uart_transmit_string("Enter index of User\r\n");
	uart_recie(&user_index);
		 if((user_index+1)>count_users){
				uart_transmit_string("\r\n");
							uart_transmit_string("enter right index\r\n");
			}
		 //wait for admin to enter user index
		else if((user_index<=count_users) && (users[user_index-48].username[0]!=0) && (users[user_index-48].username[1]!=0) && (users[user_index-48].username[2]!=0) && (users[user_index-48].username[3]!=0))
	// check for array elment not equal zero as already deleted
	{
		while(digit_1<4)
		{
			write_eeprom(0xA0,name_address_u1+(0x08)*(user_index-48)+digit_1,remove_sign); //delete data of choosen user in eeprom using TWI
			// subtract index from 48 to get number of user
			write_eeprom(0xA0,pass_address_u1+(0x08)*(user_index-48)+digit_1,remove_sign); //delete data of choosen user in eeprom using TWI
			users[user_index-48].username[digit_1]=0;
			users[user_index-48].userpass[digit_1]=0;
			digit_1++;
		}
		digit_1=0;
		while(digit_1<5){
			write_eeprom(0xA0,led_status_u+(0x05)*(user_index-48)+(digit_1),remove_sign);
			digit_1++;
		}
		digit_1=0;
		//count_users--;
	   //write_eeprom(0xA0,users_address_add,count_users);
	   uart_transmit_string("\r\n");
	   uart_transmit_string("User Removed Successfully\r\n");
	   unsigned char count_index;
	   for(count_index=user_index;count_index<count_users;count_index++)
	   {
			while(digit_1<4)
			{
				users[(count_index-48)].username[digit_1]=users[(count_index-48)+1].username[digit_1];
				users[(count_index-48)].userpass[digit_1]=users[(count_index-48)+1].userpass[digit_1];
				write_eeprom(0xA0,name_address_u1+(0x08)*(count_index-48)+digit_1,users[(count_index-48)].username[digit_1]);
				write_eeprom(0xA0,pass_address_u1+(0x08)*(count_index-48)+digit_1,users[(count_index-48)].userpass[digit_1]);
				digit_1++;
			}
			 digit_1=0;
			uint8 led_buffer=0;
			uint8 led_buffer_arr[5]={0,0,0,0,0};
				while(digit_1<5){
					 led_buffer=0;

			read_fromEEPROM(&led_buffer,0xA0,led_status_u+((0x05)*(count_index-47))+(digit_1));
			led_buffer_arr[digit_1]=led_buffer;
			write_eeprom(0xA0,led_status_u+((0x05)*(count_index-47))+(digit_1),remove_sign);
			write_eeprom(0xA0,led_status_u+((0x05)*(count_index-48))+(digit_1),led_buffer_arr[digit_1]);


					digit_1++;
				}
				 digit_1=0;
			/*	while(digit_1<5){
					write_eeprom(0xA0,led_status_u+(0x05)*(count_index-48)+1+(digit_1),remove_sign);
								write_eeprom(0xA0,led_status_u+(0x05)*(count_index-48)+(digit_1),led_buffer[digit_1]);
								digit_1++;
							}
				 digit_1=0;*/

	   }
	   count_users--;
	   	   write_eeprom(0xA0,users_address_add,count_users);
	   digit_1=0;
		}
		/*else{
			uart_transmit_string("\r\n");
			uart_transmit_string("enter right index\r\n");
		}
*/
	//count_users--;
	  // write_eeprom(0xA0,users_address_add,count_users);
	}
}
void user_menu_data()
{uint8 counter_2=0;
	admin_state=0;
	struct User users_check;

	unsigned char position=0;
	while(counter<3)
	{key=key_not_pressed;
	LCD_Clear_Display();
		LCD_Send_String_Row_Column(0,0,"enter_name");
		for(position=0;position<4;position++){
			key=key_not_pressed;
			do{
				key=Keypad_get_pressed_key();
				_delay_ms(300);

				users_check.username[position]=key;
				LCD_GoTO_Row_Column(1,position);
				LCD_Send_character(key);

			}while(key==key_not_pressed);
		}
		_delay_ms(1000);
		LCD_Clear_Display();
		key=key_not_pressed;
	_delay_ms(300);
	LCD_Send_String_Row_Column(0,0,"enter_pin_4_num");
	for(position=0;position<4;position++){
			key=key_not_pressed;
			do{
				key=Keypad_get_pressed_key();
				_delay_ms(300);
				users_check.userpass[position]=key;
				LCD_GoTO_Row_Column(1,position);
				LCD_Send_character(key);
			}while(key==key_not_pressed);
		}
	_delay_ms(1000);
			LCD_Clear_Display();
			key=key_not_pressed;

		while(user_index<9)
		{

for(digit_1=0;digit_1<4;digit_1++){
		  if((users_check.username[digit_1]== users[user_index].username[digit_1])  && (users_check.userpass[digit_1]== users[user_index].userpass[digit_1] ))
			{
			  counter_2++;
			}
		  else{
			  counter_2=0;
			  break;
              }

}
if(counter_2==4){
		  LCD_Send_String_Row_Column(0,0,"Welcome_Home");
				user_state=1;
				_delay_ms(1000);
					while(user_state){

										LCD_Clear_Display();
										menu_user();
											do{
												key=Keypad_get_pressed_key();
												_delay_ms(200);
											}while(key==key_not_pressed);
											_delay_ms(500);
											LCD_Clear_Display();
											switch (key){
											case '1':

											{admin_state=0;
												//read_fromEEPROM(&data_admin_led,0xA0,led_status_ad);
										//	read_fromEEPROM(&data_user_led,0xA0,led_status_u);

										 if(admin_state==1){
											control_leds_admin(data_admin_led);
											uart_transmit_string("enter led 1~5");
											uart_recie(&key);
											control_leds_admin(key);
										}
										else{
											digit_1=0;

											while(digit_1<5){
												read_fromEEPROM(&data_user_led,0xA0,led_status_u+((0x05)*(user_index))+(digit_1));
												control_leds_user(data_user_led);
												data_user_led=0;
												digit_1++;

											}
											LCD_Clear_Display();
											LCD_Send_String_Row_Column(0,0,"1-open");
											LCD_Send_String_Row_Column(1,0,"2-off");
											do{
											     key=Keypad_get_pressed_key();
											 	_delay_ms(300);
												}while(key==key_not_pressed);
											data_user_led=key_not_pressed;
											switch(key){
											case'1':
											{
												LCD_Clear_Display();

												LCD_Send_String_Row_Column(0,0,"enter led 1~5");
												do{
													data_user_led=Keypad_get_pressed_key();
													_delay_ms(300);
													}while(data_user_led==key_not_pressed);

												control_leds_user(data_user_led);
												user_state=1;
												key=key_not_pressed;
												break;

											}
											case'2':
											{
											LCD_Clear_Display();
											LCD_Send_String_Row_Column(0,0,"enter led 1~5");
											do{
												data_user_led=Keypad_get_pressed_key();
												_delay_ms(300);
												}while(data_user_led==key_not_pressed);
											clear_led(data_user_led);
											user_state=1;
											key=key_not_pressed;
											break;

											}
											}
											data_user_led=0;
											digit_1=0;
											//control_leds_user(data_user_led);
											/*LCD_Send_String_Row_Column(0,0,"enter led 1~5");
											do{
												key=Keypad_get_pressed_key();
											}while(key==key_not_pressed);
											control_leds_user(key);*/
										}
											key=key_not_pressed;

											user_state=1;
												break;
											}
											case '2':
											{ //init_fast_pwm();
												AC_Control();
												key=key_not_pressed;
												break;
											}
											case '3':
											{
												Dimmer_Control();
												key=key_not_pressed;
												break;
											}
											case '4':
											{led_off();
												user_state=0;

												key=key_not_pressed;
												break;
											}
											default:
											{
												key=key_not_pressed;
												break;
											}

											}
										}
										break;
}
user_index++;
			}
		if(counter_2==0){

			_delay_ms(500);
			    LCD_Clear_Display();
			    LCD_Send_String_Row_Column(0,0,"user_not_found");
			    _delay_ms(500);
			    counter++;
			  user_index=0;
		}
		break;
		}
	if(counter==3)

											{
												_delay_ms(500);
														LCD_Clear_Display();
														LCD_Send_String_Row_Column(0,0,"system_off");
														_delay_ms(500);
														//buzzer();
														LCD_Clear_Display();
														counter=0;
											}

}
void control_leds_admin(unsigned char led_choose){
	unsigned char data=0;
	DDRC|=(1<<PC2)|(1<<PC3);
	DDRD|=(1<<PD2)|(1<<PD3);
	DDRA|=(1<<PA7);
	_delay_ms(100);
	LCD_Clear_Display();
	//write_eeprom(0xA0,led_status_ad,led_choose);
	//read_fromEEPROM(&data,0xA0,led_status_ad);
	switch(led_choose){
	case'1':
		write_eeprom(0xA0,led_status_ad+(led_choose-48),led_choose);
		PORTC|=(1<<PC2);
		_delay_ms(100);
		LCD_Send_String_Row_Column(0,0,"led_1_on");
		break;
	case'2':
		write_eeprom(0xA0,led_status_ad+(led_choose-48),led_choose);
		PORTC|=(1<<PC3);
		_delay_ms(100);
		LCD_Send_String_Row_Column(0,0,"led_2_on");
		break;
	case '3':
		write_eeprom(0xA0,led_status_ad+(led_choose-48),led_choose);
		PORTD|=(1<<PD2);
		_delay_ms(100);
		LCD_Send_String_Row_Column(0,0,"led_3_on");
	break;
	case'4':
		write_eeprom(0xA0,led_status_ad+(led_choose-48),led_choose);
		PORTD|=(1<<PD3);
		_delay_ms(100);
		LCD_Send_String_Row_Column(0,0,"led_4_on");
	break;
	case '5':
		write_eeprom(0xA0,led_status_ad+(led_choose-48),led_choose);
		PORTA|=(1<<PA7);
		_delay_ms(100);
		LCD_Send_String_Row_Column(0,0,"led_5_on");
	break;
	}
}
void control_leds_user(unsigned char led_choose){
//	unsigned char data=0;
	 uint8 counter_led=0;
	DDRC|=(1<<PC2)|(1<<PC3);
	DDRD|=(1<<PD2)|(1<<PD3);
DDRA|=(1<<PA7);
_delay_ms(100);
LCD_Clear_Display();
while(counter_led<1){
//write_eeprom(0xA0,led_status_u+(user_index-48)+(counter_led-1),led_choose);
//read_fromEEPROM(&data,0xA0,led_status_u);
	switch(led_choose){
	case'1':
		PORTC|=(1<<PC2);
		_delay_ms(100);
		counter_led=1;
		write_eeprom(0xA0,led_status_u+((0x05)*(user_index)+(counter_led-1)),led_choose);
		break;
	case'2':
		PORTC|=(1<<PC3);
		_delay_ms(100);
		counter_led=2;
		write_eeprom(0xA0,led_status_u+((0x05)*(user_index)+(counter_led-1)),led_choose);
		break;
	case '3':
		PORTD|=(1<<PD2);
		_delay_ms(100);
		counter_led=3;
		write_eeprom(0xA0,led_status_u+((0x05)*(user_index)+(counter_led-1)),led_choose);
	break;
	case'4':
		PORTD|=(1<<PD3);
		_delay_ms(100);
		counter_led=4;
		write_eeprom(0xA0,led_status_u+((0x05)*(user_index)+(counter_led-1)),led_choose);
	break;
	case '5':
		PORTA|=(1<<PA7);
		_delay_ms(100);
		counter_led=5;
		write_eeprom(0xA0,led_status_u+((0x05)*(user_index)+(counter_led-1)),led_choose);
	break;
	default:{

	        counter_led=7;
	        break;
	    }
	}
}
counter_led=0;
}
void led_off()
{
	//Turning all Led Pins off
	CLEAR_BIT(PORTC,PC2);
	CLEAR_BIT(PORTC,PC3);
	CLEAR_BIT(DDRD,PD3);
	CLEAR_BIT(DDRD,PD2);
	CLEAR_BIT(DDRA,PA7);
	CLEAR_BIT(PORTC,PC3);
	CLEAR_BIT(PORTD,PD3);
	CLEAR_BIT(PORTD,PD2);
	CLEAR_BIT(PORTA,PA7);
}

void init_fast_pwm()
{
	    // fast PWM mode 15
		DDRD|=(1<<PD4);                     // oc1b as output
		TCCR1A|=(1<<WGM10)|(1<<WGM11);     //for mode 15 fast PWM
		TCCR1B|=(1<<WGM12)|(1<<WGM13);    //for mode 15 fast PWM
		TCCR1A|=(1<<COM1B1);             // for non inverted mode
		TCCR1B|=(1<<CS10)|(1<<CS11);    // prescaler over 64  (8000000/64=125000 hz)
		//****************************************************
		OCR1AH=0xff;  //  ocr1a ,  from data sheet, is top most value
		OCR1AL=0xff; //   ocr1a ,  from data sheet, is top most value
		// note: now frequency becomes 125000/(2^16)=1.907346 hz
		//that mean that output frqueny =1.907346 hz
		//speed of motor is slow
		CLEAR_BIT(DDRD,DDD5);
}
void PWM_init() {
    // Set Fast PWM mode with non-inverting output on pin OC1A (PD5)
    TCCR1A |= (1 << COM1A1) | (1 << WGM11) | (1 << WGM10);
    TCCR1B |= (1 << WGM12) | (1 << CS11); // Set prescaler to 8
    DDRD |= (1 << DDD5); // Set OC1A (PD5) pin as output
    CLEAR_BIT(DDRD,DDD4);
}
void duty_cycle_update(unsigned int duty_cycle)
{
	unsigned long ocrb=0;
	ocrb=(((duty_cycle*65536)/100)-1);
    OCR1BH=(ocrb>>8);
    OCR1BL=ocrb;
}
void PWM_set_duty_cycle(uint16_t duty_cycle) {
    OCR1A = duty_cycle;
}
void AC_Control()
{
	SET_BIT(DDRA,PA6);
	SET_BIT(DDRA,PA4);
	adcA = (int)(read_adc(5)*5.0)/1024.0;
	temperature=adcA/0.01;
	while(1)
	{
	LCD_IntToString((int) temperature,tempSTR);
	LCD_Send_String_Row_Column(1,0,"Temperature");
	LCD_Send_String_Row_Column(1,13,tempSTR);
	while(temperature>21)
	{//DDRA|=(1<<PA6);
	//PORTA|=(1<<PA6);
		//ON
		//SET_BIT(PORTA,PA6);
		SET_BIT(PORTA,PA4);
		duty_cycle_update(100);
		temperature--;
		_delay_ms(500);
		LCD_IntToString((int) temperature,tempSTR);
		LCD_Send_String_Row_Column(1,0,"Temperature");
		LCD_Send_String_Row_Column(1,13,tempSTR);
	}
	 if(temperature<21)
	{
		//OFF
		 fan_off();
		   break;
	}
	}
}
void fan_off(){
	//Clearing all pins of L293D which control the rotation of the fan
	CLEAR_BIT(PORTA,PA6);
	CLEAR_BIT(PORTA,PA4);
	CLEAR_BIT(DDRA,PA6);
	CLEAR_BIT(DDRA,PA4);
	//Normal Mode of Operation
		CLEAR_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1B,WGM11);
		CLEAR_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
		duty_cycle_update(0);
}
void Dimmer_Control()
{PWM_init();
uint8 i=0; //as counter
	LCD_Clear_Display();
	if(admin_state==1)
	{
		LCD_Send_String_Row_Column(0,0,"Dimmer On");
		uart_transmit_string("enter intensity from 1~5");
		uart_recie(&brightness);
		brightness=((brightness-48)*(256/5));// equation to get desired brigthness
		//256/5 to get desired step size

		  for (i = 0; i < brightness; i++) {
		            PWM_set_duty_cycle(i);
		            _delay_ms(3); // Adjust the delay as needed for the desired brightness change speed
		        }
		  brightness=key_not_pressed;

	}
	else if(user_state==1){
		LCD_Send_String_Row_Column(0,0,"enter intensity");
		LCD_Send_String_Row_Column(1,0,"from 1~5");
		do{
			brightness=Keypad_get_pressed_key();
			_delay_ms(100);

		}while(brightness==key_not_pressed);
		LCD_Clear_Display();
		_delay_ms(5);
		LCD_Send_String_Row_Column(0,0,"Dimmer On");
		brightness=((brightness-48)*(256/5));
		  for (i = 0; i < brightness; i++) {
		            PWM_set_duty_cycle(i);
		            _delay_ms(3); // Adjust the delay as needed for the desired brightness change speed
		        }
		  brightness=key_not_pressed;
			//CLEAR_BIT(DDRD,DDD5);
			LCD_Clear_Display();

	}


 	/*  while (1) {
        // Vary the brightness from 0 to 1023 and then back to 0
        for (brightness = 0; brightness < 255; brightness++) {
            PWM_set_duty_cycle(brightness);
            _delay_ms(5); // Adjust the delay as needed for the desired brightness change speed
        }
        for (brightness = 255; brightness > 0; brightness--) {
            PWM_set_duty_cycle(brightness);
            _delay_ms(5); // Adjust the delay as needed for the desired brightness change speed
        				}

    	CLEAR_BIT(DDRD,DDD5);
    	LCD_Clear_Display();
        	break;
		}
		*/
}
void buzzer()
{
	SET_BIT(DDRA,PA4);
	SET_BIT(PORTA,PA4);
	_delay_ms(3000);
	//system shutdown
	CLEAR_BIT(PORTA,PA4);
}
void clear_led(uint8 choose_leds){
if(admin_state==1){
	//unsigned char data=0;
	_delay_ms(100);
		LCD_Clear_Display();
	//	write_eeprom(0xA0,led_status_ad,choose_leds);
		//read_fromEEPROM(&data,0xA0,led_status_ad);
		switch(choose_leds){
		case'1':
			write_eeprom(0xA0,led_status_ad+(choose_leds-48),remove_sign);
			CLEAR_BIT(PORTC,PC2);
			_delay_ms(100);
			LCD_Send_String_Row_Column(0,0,"led_1_oFF");
			break;
		case'2':
			write_eeprom(0xA0,led_status_ad+(choose_leds-48),remove_sign);

			CLEAR_BIT(PORTC,PC3);
			_delay_ms(100);
			LCD_Send_String_Row_Column(0,0,"led_2_OFF");
			break;
		case '3':
			write_eeprom(0xA0,led_status_ad+(choose_leds-48),remove_sign);

			CLEAR_BIT(PORTD,PD2);
			_delay_ms(100);
			LCD_Send_String_Row_Column(0,0,"led_3_on");
		break;
		case'4':
			write_eeprom(0xA0,led_status_ad+(choose_leds-48),remove_sign);
			CLEAR_BIT(PORTD,PD3);

			_delay_ms(100);
			LCD_Send_String_Row_Column(0,0,"led_4_oFF");
		break;
		case '5':
			write_eeprom(0xA0,led_status_ad+(choose_leds-48),remove_sign);
			CLEAR_BIT(PORTA,PA7);
			_delay_ms(100);
			LCD_Send_String_Row_Column(0,0,"led_5_oFF");
		break;
		}

}
else if(user_state==1){
	 uint8 counter_led=0;
	_delay_ms(100);
	LCD_Clear_Display();
	while(counter_led<1){
	//write_eeprom(0xA0,led_status_u+(user_index-48)+(counter_led-1),led_choose);
	//read_fromEEPROM(&data,0xA0,led_status_u);
		switch(choose_leds){
		case'1':
			CLEAR_BIT(DDRC,PC2);
		CLEAR_BIT(PORTC,PC2);
			_delay_ms(100);
			counter_led=1;
			write_eeprom(0xA0,led_status_u+((0x05)*(user_index)+(counter_led-1)),remove_sign);
			break;
		case'2':
			CLEAR_BIT(DDRC,PC3);
			CLEAR_BIT(PORTC,PC3);
			_delay_ms(100);
			counter_led=2;
			write_eeprom(0xA0,led_status_u+((0x05)*(user_index)+(counter_led-1)),remove_sign);
			break;
		case '3':

			CLEAR_BIT(DDRD,PD2);
			CLEAR_BIT(PORTD,PD2);
			_delay_ms(100);
			counter_led=3;
			write_eeprom(0xA0,led_status_u+((0x05)*(user_index)+(counter_led-1)),remove_sign);
		break;
		case'4':
			PORTD|=(1<<PD3);
			CLEAR_BIT(DDRD,PD3);
			CLEAR_BIT(PORTD,PD3);
			_delay_ms(100);
			counter_led=4;
			write_eeprom(0xA0,led_status_u+((0x05)*(user_index)+(counter_led-1)),remove_sign);
		break;
		case '5':

			CLEAR_BIT(DDRA,PA7);
			CLEAR_BIT(PORTA,PA7);
			_delay_ms(100);
			counter_led=5;
			write_eeprom(0xA0,led_status_u+((0x05)*(user_index)+(counter_led-1)),remove_sign);
		break;
		default:{

		        counter_led=7;
		        break;
		    }
		}
	}
	counter_led=0;


}




}
