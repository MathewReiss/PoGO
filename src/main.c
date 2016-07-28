#include <pebble.h>

Window *window;

#define POGO 0
#define VALOR 1
#define MYSTIC 2
#define INSTINCT 3
int current = 0;

GBitmap *current_bg;
GRect current_rect;

char custom_text[32];
char optional_buffer[32];

#define NOTHING 0
#define TEAM_NAME 1
#define DATE_MDY 2
#define DATE_DMY 3
#define STEPS_COMMA 4
#define STEPS_DOT 5
#define DISTANCE_DOT 6
#define DISTANCE_COMMA 7
#define CUSTOM 8
int option = 0;

#ifdef PBL_RECT
	#ifndef PBL_COLOR
		#define VALOR_GRECT GRect(0,0,144,142)
		#define INSTINCT_GRECT GRect(0,6,144,133)
		#define MYSTIC_GRECT GRect(13,9,117,124)
		#define POGO_GRECT GRect(0,27,144,90)

		#define VALOR_GRECT_NOTHING VALOR_GRECT
		#define INSTINCT_GRECT_NOTHING INSTINCT_GRECT
		#define MYSTIC_GRECT_NOTHING MYSTIC_GRECT
	#else
		#define VALOR_GRECT GRect(10,20,125,123)
		#define INSTINCT_GRECT GRect(10,26,125,116)
		#define MYSTIC_GRECT GRect(14,20,117,124)
		#define POGO_GRECT GRect(0,27,144,90)

		#define VALOR_GRECT_NOTHING GRect(10,10,125,123)
		#define INSTINCT_GRECT_NOTHING GRect(10,16,125,116)
		#define MYSTIC_GRECT_NOTHING GRect(14,10,117,124)
	#endif
#elif PBL_ROUND
	#define VALOR_GRECT GRect(28,31,125,123)
	#define INSTINCT_GRECT GRect(27,36,125,116)
	#define MYSTIC_GRECT GRect(31,28,117,124)
	#define POGO_GRECT GRect(27,50,125,79)

	#define VALOR_GRECT_NOTHING VALOR_GRECT
	#define INSTINCT_GRECT_NOTHING INSTINCT_GRECT
	#define MYSTIC_GRECT_NOTHING MYSTIC_GRECT
#endif

GColor bg_color;

bool showBattery = false;

int hour = 0, minute = 0;

bool timerActive = false;
bool timerEnabled = false;

char timeBuffer[16];
char dateBufferMDY[16];
char dateBufferDMY[16];
char stepsBufferComma[16];
char stepsBufferDot[16];
char distanceBufferComma[16];
char distanceBufferDot[16];

char timerBuffer[16];

void draw_window(Layer *layer, GContext *ctx){
	graphics_context_set_fill_color(ctx, bg_color);
	graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
	
	graphics_context_set_compositing_mode(ctx, GCompOpSet);
	graphics_draw_bitmap_in_rect(ctx, current_bg, current_rect);
	
	graphics_context_set_text_color(ctx, gcolor_legible_over(bg_color));
	graphics_draw_text(ctx, timeBuffer, fonts_get_system_font(FONT_KEY_LECO_20_BOLD_NUMBERS), GRect(0,PBL_IF_RECT_ELSE(141,149),PBL_IF_RECT_ELSE(144,180),20), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
	
	if(timerActive){
		graphics_draw_text(ctx, timerBuffer, fonts_get_system_font(FONT_KEY_LECO_20_BOLD_NUMBERS), GRect(0, PBL_IF_RECT_ELSE(-2,6),PBL_IF_RECT_ELSE(144,180),20), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
	}
	
	if(option != NOTHING && !timerActive){
		switch(option){
			case TEAM_NAME:
				if(current == VALOR) graphics_draw_text(ctx, "VALOR", fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD), GRect(0,PBL_IF_RECT_ELSE(-4,4),PBL_IF_RECT_ELSE(144,180),20), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
				else if(current == MYSTIC) graphics_draw_text(ctx, "MYSTIC", fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD), GRect(0,PBL_IF_RECT_ELSE(-2,6),PBL_IF_RECT_ELSE(144,180),20), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
				else if(current == INSTINCT) graphics_draw_text(ctx, "INSTINCT", fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD), GRect(0,PBL_IF_RECT_ELSE(-2,6),PBL_IF_RECT_ELSE(144,180),20), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
			break;
				
			case DATE_MDY:
				graphics_draw_text(ctx, dateBufferMDY, fonts_get_system_font(FONT_KEY_LECO_20_BOLD_NUMBERS), GRect(0,PBL_IF_RECT_ELSE(-2,6),PBL_IF_RECT_ELSE(144,180),20), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
			break;
				
			case DATE_DMY:
				graphics_draw_text(ctx, dateBufferDMY, fonts_get_system_font(FONT_KEY_LECO_20_BOLD_NUMBERS), GRect(0,PBL_IF_RECT_ELSE(-2,6),PBL_IF_RECT_ELSE(144,180),20), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
			break;
				
			case STEPS_COMMA:
				graphics_draw_text(ctx, stepsBufferComma, fonts_get_system_font(FONT_KEY_LECO_20_BOLD_NUMBERS), GRect(0,PBL_IF_RECT_ELSE(-2,6),PBL_IF_RECT_ELSE(144,180),20), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
			break;
				
			case STEPS_DOT:
				graphics_draw_text(ctx, stepsBufferDot, fonts_get_system_font(FONT_KEY_LECO_20_BOLD_NUMBERS), GRect(0,PBL_IF_RECT_ELSE(-2,6),PBL_IF_RECT_ELSE(144,180),20), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
			break;
				
			case DISTANCE_COMMA:
				graphics_draw_text(ctx, distanceBufferComma, fonts_get_system_font(FONT_KEY_LECO_20_BOLD_NUMBERS), GRect(0,PBL_IF_RECT_ELSE(-2,6),PBL_IF_RECT_ELSE(144,180),20), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
			break;
					
			case DISTANCE_DOT:
				graphics_draw_text(ctx, distanceBufferDot, fonts_get_system_font(FONT_KEY_LECO_20_BOLD_NUMBERS), GRect(0,PBL_IF_RECT_ELSE(-2,6),PBL_IF_RECT_ELSE(144,180),20), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
			break;
				
			case CUSTOM:
				if(current == VALOR) graphics_draw_text(ctx, custom_text, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD), GRect(0,PBL_IF_RECT_ELSE(-4,4),PBL_IF_RECT_ELSE(144,180),20), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
				else graphics_draw_text(ctx, custom_text, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD), GRect(0,PBL_IF_RECT_ELSE(-2,6),PBL_IF_RECT_ELSE(144,180),20), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
			break;
				
			default:
				if(current == VALOR) graphics_draw_text(ctx, "VALOR", fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD), GRect(0,PBL_IF_RECT_ELSE(-4,4),PBL_IF_RECT_ELSE(144,180),20), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
				else if(current == MYSTIC) graphics_draw_text(ctx, "MYSTIC", fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD), GRect(0,PBL_IF_RECT_ELSE(-2,6),PBL_IF_RECT_ELSE(144,180),20), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
				else if(current == INSTINCT) graphics_draw_text(ctx, "INSTINCT", fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD), GRect(0,PBL_IF_RECT_ELSE(-2,6),PBL_IF_RECT_ELSE(144,180),20), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
			break;
			}
		}
	
		if(showBattery){
			graphics_context_set_fill_color(ctx, gcolor_legible_over(bg_color));
			#ifdef PBL_RECT
			graphics_fill_rect(ctx, GRect(0,168-168*battery_state_service_peek().charge_percent/100,2,168*battery_state_service_peek().charge_percent/100), 0, GCornerNone);
			graphics_fill_rect(ctx, GRect(142,168-168*battery_state_service_peek().charge_percent/100,2,168*battery_state_service_peek().charge_percent/100), 0, GCornerNone);
			#elif PBL_ROUND
			graphics_fill_radial(ctx, layer_get_bounds(layer), GOvalScaleModeFitCircle, 4, (TRIG_MAX_ANGLE / 2) - ( (battery_state_service_peek().charge_percent*TRIG_MAX_ANGLE) / (2*100) ), (TRIG_MAX_ANGLE / 2) );
			graphics_fill_radial(ctx, layer_get_bounds(layer), GOvalScaleModeFitCircle, 4, (TRIG_MAX_ANGLE / 2), (TRIG_MAX_ANGLE / 2) + (battery_state_service_peek().charge_percent*TRIG_MAX_ANGLE) / (2*100) );
			#endif
		}
}

void choose_team(){
	if(current_bg != NULL) gbitmap_destroy(current_bg);
	
	switch(current){
		case POGO: 
			current_bg = gbitmap_create_with_resource(RESOURCE_ID_POGO); 
			current_rect = POGO_GRECT;
		break;
		
		case VALOR: 
			current_bg = gbitmap_create_with_resource(RESOURCE_ID_VALOR); 
			current_rect = option == NOTHING ? VALOR_GRECT_NOTHING : VALOR_GRECT;
		break;
		
		case MYSTIC: 
			current_bg = gbitmap_create_with_resource(RESOURCE_ID_MYSTIC); 
			current_rect = option == NOTHING ? MYSTIC_GRECT_NOTHING : MYSTIC_GRECT;
		break;
		
		case INSTINCT: 
			current_bg = gbitmap_create_with_resource(RESOURCE_ID_INSTINCT); 
			current_rect = option == NOTHING ? INSTINCT_GRECT_NOTHING : INSTINCT_GRECT;
		break;
		
		default: 
			current_bg = gbitmap_create_with_resource(RESOURCE_ID_POGO); 
			current_rect = POGO_GRECT;
		break;
	}
	
	#ifndef PBL_COLOR
		if(current != POGO && !gcolor_equal(bg_color, GColorWhite)){
			GColor *pal = gbitmap_get_palette(current_bg);
			pal[0] = gcolor_legible_over(pal[0]);
			pal[1] = gcolor_legible_over(pal[1]);
			pal[2] = gcolor_legible_over(pal[2]);
		}
	#endif
	
	layer_mark_dirty(window_get_root_layer(window));
}

void tick(struct tm *tick_time, TimeUnits units){
	if(clock_is_24h_style()){
		hour = tick_time->tm_hour;
	}
	else{
		if(tick_time->tm_hour%12 == 0) hour = 12;
		else hour = tick_time->tm_hour%12;
	}
	
	minute = tick_time->tm_min;
	
	snprintf(timeBuffer, sizeof(timeBuffer), clock_is_24h_style() ? "%02d:%02d" : "%d:%02d", hour, minute);

	#ifdef PBL_RECT
	snprintf(dateBufferDMY, sizeof(dateBufferDMY), "%02d / %02d / %02d", tick_time->tm_mday, tick_time->tm_mon+1, tick_time->tm_year-100);
	snprintf(dateBufferMDY, sizeof(dateBufferMDY), "%d / %d / %d", tick_time->tm_mon+1, tick_time->tm_mday, tick_time->tm_year-100);
	#elif PBL_ROUND
	snprintf(dateBufferDMY, sizeof(dateBufferDMY), "%02d / %02d", tick_time->tm_mday, tick_time->tm_mon+1);
	snprintf(dateBufferMDY, sizeof(dateBufferMDY), "%d / %d", tick_time->tm_mon+1, tick_time->tm_mday);
	#endif
	
	HealthServiceAccessibilityMask steps = health_service_metric_accessible(HealthMetricStepCount, time_start_of_today(), time(NULL));
	if(steps & HealthServiceAccessibilityMaskAvailable){
		int num_steps = health_service_sum_today(HealthMetricStepCount);
		if(num_steps >= 1000){
			snprintf(stepsBufferComma, sizeof(stepsBufferComma), "%d,%03d", num_steps / 1000, num_steps % 1000);
			snprintf(stepsBufferDot, sizeof(stepsBufferDot), "%d.%03d", num_steps / 1000, num_steps % 1000);
		}
		else{
			snprintf(stepsBufferComma, sizeof(stepsBufferComma), "%d", num_steps);
			snprintf(stepsBufferDot, sizeof(stepsBufferDot), "%d", num_steps);
		}
	}
	
	HealthServiceAccessibilityMask dist = health_service_metric_accessible(HealthMetricWalkedDistanceMeters, time_start_of_today(), time(NULL));
	if(dist & HealthServiceAccessibilityMaskAvailable){
		float dist_m = health_service_sum_today(HealthMetricWalkedDistanceMeters);
		
		if(health_service_get_measurement_system_for_display(HealthMetricWalkedDistanceMeters) == MeasurementSystemImperial){
			dist_m = (float)(dist_m * 0.000621371f);
		}
		else{
			dist_m = (float)(dist_m * 0.001f);
		}
		
		if( (int)(dist_m * 100) % 10 >= 5 ) dist_m += 0.05f;
		
		snprintf(distanceBufferDot, sizeof(distanceBufferDot), "%d.%01d", (int)dist_m, (int)(dist_m*10)%10);
		snprintf(distanceBufferComma, sizeof(distanceBufferComma), "%d,%01d", (int)dist_m, (int)(dist_m*10)%10);
	}

	choose_team();
}

int min_left = 0, sec_left = 0;
AppTimer *stopTimer;
bool timerRunning = false;

void delay(){
	timerRunning = false;
}

void stop_tick(){
	sec_left--;
	
	if(sec_left == -1){
		sec_left = 59;
		min_left--;
		
		if(min_left == -1){
			vibes_long_pulse();
			timerActive = false;
			app_timer_register(1100, delay, NULL);
		}
	}
	
	snprintf(timerBuffer, sizeof(timerBuffer),"%d:%02d", min_left, sec_left);
	layer_mark_dirty(window_get_root_layer(window));
	
	if(timerActive && timerRunning) stopTimer = app_timer_register(1000, stop_tick, NULL);
}

void tap(AccelAxisType type, void *context){
	if(timerEnabled){
		if(timerActive){
			timerActive = false;
			timerRunning = false;
			app_timer_cancel(stopTimer);
		}
		else{
			if(timerRunning) return;
			vibes_double_pulse();
			timerActive = true;
			timerRunning = true;
			min_left = 5;
			sec_left = 1;
			stopTimer = app_timer_register(0, stop_tick, NULL);
		}
	}
	layer_mark_dirty(window_get_root_layer(window));
}

void inbox(DictionaryIterator *iter, void *context){
	Tuple *bg_color_t = dict_find(iter, MESSAGE_KEY_BackgroundColor);
	if(bg_color_t){
		bg_color = GColorFromHEX(bg_color_t->value->int32);	
		persist_write_int(MESSAGE_KEY_BackgroundColor, bg_color.argb);
	}
	
	Tuple *team_t = dict_find(iter, MESSAGE_KEY_Team);
	if(team_t){
		current = atoi(team_t->value->cstring);
		persist_write_int(MESSAGE_KEY_Team, current);
	}
	
	Tuple *optional_t = dict_find(iter, MESSAGE_KEY_Optional);
	if(optional_t){
		option = atoi(optional_t->value->cstring);
		persist_write_int(MESSAGE_KEY_Optional, option);
	}
	
	Tuple *custom_text_t = dict_find(iter, MESSAGE_KEY_CustomText);
	if(custom_text_t){
		strncpy(custom_text, custom_text_t->value->cstring, sizeof(custom_text));
		persist_write_string(MESSAGE_KEY_CustomText, custom_text);
	}
	
	Tuple *show_battery_t = dict_find(iter, MESSAGE_KEY_ShowBattery);
	if(show_battery_t){
		showBattery = show_battery_t->value->int32 == 1;
		persist_write_bool(MESSAGE_KEY_ShowBattery, showBattery);
	}
	
	Tuple *timer_enabled_t = dict_find(iter, MESSAGE_KEY_Pokestop);
	if(timer_enabled_t){
		timerEnabled = timer_enabled_t->value->int32 == 1;
		persist_write_bool(MESSAGE_KEY_Pokestop, timerEnabled);
		
		if(timerEnabled){
			accel_tap_service_subscribe((AccelTapHandler)tap);
		}
	}
	
	choose_team();
}

int main(void){
	app_message_register_inbox_received(inbox);
	app_message_open(128,128);
	
	window = window_create();
	layer_set_update_proc(window_get_root_layer(window), draw_window);

	if(persist_exists(MESSAGE_KEY_BackgroundColor)) bg_color = (GColor){ .argb = persist_read_int(MESSAGE_KEY_BackgroundColor) };
	else bg_color = GColorWhite;	
	
	if(persist_exists(MESSAGE_KEY_Team)) current = persist_read_int(MESSAGE_KEY_Team);
	
	if(persist_exists(MESSAGE_KEY_Optional)) option = persist_read_int(MESSAGE_KEY_Optional);
	
	if(persist_exists(MESSAGE_KEY_CustomText)) persist_read_string(MESSAGE_KEY_CustomText, custom_text, sizeof(custom_text));
	
	if(persist_exists(MESSAGE_KEY_ShowBattery)) showBattery = persist_read_bool(MESSAGE_KEY_ShowBattery);
	
	if(persist_exists(MESSAGE_KEY_Pokestop)) timerEnabled = persist_read_bool(MESSAGE_KEY_Pokestop);
	
	if(timerEnabled){
		accel_tap_service_subscribe((AccelTapHandler)tap);
	}
	
	choose_team();
	
	time_t now = time(NULL);
	struct tm *ltime = localtime(&now);
	tick(ltime, MINUTE_UNIT);
	
	tick_timer_service_subscribe(MINUTE_UNIT, tick);
		
	window_stack_push(window,true);
	
	app_event_loop();
}