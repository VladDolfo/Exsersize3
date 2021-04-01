Action()
{
	

	
	/* intenary */
	
	
	//Total Charge: $ 
	web_reg_save_param_ex("ParamName=Charge",
	                     "LB=Total Charge: $ ",
	                    "RB= <BR/>",
	                   "Ordinal=ALL",LAST);
	
	

	web_url("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t11.inf", 
		"Mode=HTML", 
		LAST);
	
	
    lr_output_message("Ticket 1 $=%d",atoi(lr_eval_string("{Charge_1}")));
	lr_output_message("Ticket 2 $=%d",atoi(lr_eval_string("{Charge_2}")));
	lr_output_message("Ticket 3 $=%d",atoi(lr_eval_string("{Charge_3}")));
	
	
//Нахождение минимума для цены билета	
	if((atoi(lr_eval_string("{Charge_1}"))<atoi(lr_eval_string("{Charge_2}"))) && (atoi(lr_eval_string("{Charge_2}"))<atoi(lr_eval_string("{Charge_3}")))){
		min=atoi(lr_eval_string("{Charge_1}"));
		lr_save_string("1","flightnum");   //Сохранение в переменную flightnum значение 1. Для подстановки в web_submit_form
	}
	if((atoi(lr_eval_string("{Charge_2}"))<atoi(lr_eval_string("{Charge_1}"))) && (atoi(lr_eval_string("{Charge_2}"))<atoi(lr_eval_string("{Charge_3}")))){
		min=atoi(lr_eval_string("{Charge_2}"));
		lr_save_string("2","flightnum");
	}
	if((atoi(lr_eval_string("{Charge_3}"))<atoi(lr_eval_string("{Charge_1}"))) && (atoi(lr_eval_string("{Charge_3}"))<atoi(lr_eval_string("{Charge_2}")))){
		min=atoi(lr_eval_string("{Charge_3}"));
		lr_save_string("3","flightnum");
	}
	
	lr_output_message("Minimum=%d",min);
	

	/* cancel flight */
	
//Запрос на отмену
	web_submit_form("itinerary.pl",ITEMDATA,
       "Name={flightnum}", "Value=on",ENDITEM,          //Постановка значения
       
       "Name=removeFlights.x","Value=36",ENDITEM,
       "Name=removeFlights.y","Value=5",ENDITEM,
       LAST);

	web_submit_data("itinerary.pl", 
		"Action=http://localhost:1080/cgi-bin/itinerary.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/itinerary.pl", 
		"Snapshot=t12.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=2", "Value=on", ENDITEM, 
		"Name=flightID", "Value={flightID}", ENDITEM, 
		"Name=flightID", "Value={flightID}", ENDITEM, 
		"Name=.cgifields", "Value=1", ENDITEM, 
		"Name=.cgifields", "Value=2", ENDITEM, 
		"Name=removeFlights.x", "Value=34", ENDITEM, 
		"Name=removeFlights.y", "Value=11", ENDITEM, 
		LAST);

	/* singoff */

	

	

	
	return 0;
}
