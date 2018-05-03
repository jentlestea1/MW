vpath %.c ./src/
vpath %.c ./src/app/
vpath %.c ./src/RT/
vpath %.c ./src/data_stream/
vpath %.c ./src/event/
vpath %.c ./src/file/
vpath %.c ./src/package/
vpath %.c ./src/pack_rule_descrip/
vpath %.c ./src/RT/
vpath %.c ./src/traffic_light/
vpath %.c ./src/vi_dev_visit_sys/
vpath %.c ./src/xml_parser/
vpath %.c ./src/BC/
vpath %.h ./include/type/
vpath %.h ./include/app/
vpath %.h ./include/RT/
vpath %.h ./include/data_stream/
vpath %.h ./include/event/
vpath %.h ./include/file/
vpath %.h ./include/package/
vpath %.h ./include/pack_rule_descrip/
vpath %.h ./include/traffic_light/
vpath %.h ./include/vi_dev_visit_sys/
vpath %.h ./include/xml_parser/
vpath %.h ./include/BC/

CCFLAGS = -I ./include/type -I ./include/app -I ./include/RT/ -I ./include/data_stream/ -I ./include/file/ -I ./include/event -I ./include/package -I ./include/pack_rule_descrip -I ./include/traffic_light -I ./include/vi_dev_visit_sys -I ./include/xml_parser -I ./include/BC -DDEBUG
ENDFALGS = -lmxml -lpthread -lm
CC = cc 
BC_OBJ = main.o manage_transport_center.o app.o BC_socket.o BC_control.o package.o \
		 control_package.o control_data_stream.o control_traffic_light.o traffic_light.o \
		 data_stream.o handle_data_package.o xml_parse.o relevant_struct_def.o \
		 address_map.o route_map.o config_1553.o handle_event.o event.o handle_event_func.o \
		 file.o

RT_OBJ = RT_socket.o RT_control.o RT.o relevant_struct_def.o file.o

all : BC RT
	
BC : $(BC_OBJ)
	$(CC) -o BC $(BC_OBJ) $(ENDFALGS)
RT : $(RT_OBJ)
	$(CC) -o RT $(RT_OBJ) $(ENDFALGS)
	mv *.o ./obj/
$(BC_OBJ): %.o: %.c
	$(CC) -c $(CCFLAGS) $< -o $@
$(RT_OBJ): %.o: %.c
	$(CC) -c $(CCFLAGS) $< -o $@

.PHONY : clean
clean:
	rm BC RT ./obj/*.o ./*.o
