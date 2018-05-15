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
vpath %.c ./src/vcan_transmit/
vpath %.c ./src/type/
vpath %.c ./src/mxml/
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
vpath %.h ./include/vcan_transmit/
vpath %.h ./include/mxml/


ifeq ($(PROTOCOL),VCAN)
	BC_CC = sparc-elf-gcc
	RT_CC = cc
	V_PROTOCOL = -D$(PROTOCOL)_PROTOCOL
else
ifeq ($(PROTOCOL),TCPIP)
	BC_CC = cc
	RT_CC = cc
	V_PROTOCOL = -DSOCKET_PROTOCOL
else
	BC_CC = cc
	RT_CC = cc
	PROTOCOL = TCPIP
	V_PROTOCOL = -DSOCKET_PROTOCOL
endif
endif
BC_CC_VERSION = `$(BC_CC) --version`
RT_CC_VERSION = `$(RT_CC) --version`

CCFLAGS = -I ./include/type -I ./include/app -I ./include/RT/ -I ./include/data_stream/ -I ./include/file/ \
		  -I ./include/event -I ./include/package -I ./include/pack_rule_descrip -I ./include/traffic_light \
		  -I ./include/vi_dev_visit_sys -I ./include/xml_parser -I ./include/BC -I ./include/vcan_transmit \
		  -I ./include/mxml  $(V_PROTOCOL) #-DVCAN_PROTOCOL #-DSOCKET_PROTOCOL #-DDEBUG

ENDFALGS = -lpthread -lm

#BC_CC = sparc-elf-gcc #-O2 #sparc-elf-gcc #-std=c89 -pedantic -Wall -Wstrict-prototypes -Wno-missing-braces -O6 -I. $*
BC_OBJ = main.o manage_transport_center.o app.o BC_socket.o BC_control.o package.o \
		 control_package.o control_data_stream.o control_traffic_light.o traffic_light.o \
		 data_stream.o handle_data_package.o xml_parse.o relevant_struct_def.o \
		 address_map.o route_map.o config_1553.o handle_event.o event.o handle_event_func.o \
		 can_sys.o can_transmit.o m_type.o mxml-attr.o mxml-entity.o mxml-file.o mxml-get.o mxml-index.o \
		 mxml-node.o mxml-private.o mxml-search.o mxml-set.o mxml-string.o
		 

RT_OBJ = RT_socket.o RT_control.o RT.o relevant_struct_def_rt.o m_type_rt.o file.o

all : PRE_OPERA BC.out RT.out
	
PRE_OPERA:
	@echo 'BC_CC : '$(BC_CC)' version : '$(BC_CC_VERSION)
	@echo 'RT_CC : '$(RT_CC)' version : '$(RT_CC_VERSION)
	@echo "PROTOCOL : "$(PROTOCOL)"\n"
	@echo '******************************************************'
	@echo '*''                 @MAKE'
	@echo '*'' @ $(MAKE) PROTOCOL=VCAN   #使用VCAN传输协议'
	@echo '*'' @ $(MAKE) PROTOCOL=TCPIP  #使用TCPIP传输协议'
	@echo '*'' @ $(MAKE)                 #等同make PROTOCOL=TCPIP'
	@echo '******************************************************'
	@echo "\n"
	@mkdir -p obj
	@rm -f BC.out RT.out ./obj/*.o ./*.o
BC.out : $(BC_OBJ)
	$(BC_CC) -o BC.out $(BC_OBJ) $(ENDFALGS)
RT.out : $(RT_OBJ)
	$(RT_CC) -o RT.out $(RT_OBJ) $(ENDFALGS)
	mv *.o ./obj/
$(BC_OBJ): %.o: %.c
	$(BC_CC) -c $(CCFLAGS) $< -o $@
$(RT_OBJ): %.o: %.c
	$(RT_CC) -c $(CCFLAGS) $< -o $@

.PHONY : clean
clean:
	rm -f BC.out RT.out ./obj/*.o ./*.o
