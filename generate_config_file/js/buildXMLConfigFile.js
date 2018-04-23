/**
 * Created by wangshaobo_ on 2017/8/6.
 */
define(['js/createEntityDataForm'], function (createEntityDataForm) {
    'use strict';//使用电子数据表格生成XML
    var XMLFileHistoryArray=[],
        createXMLFileNode=function(){
            this.fileName=null;
            this.fileContent=null;
            this.getFileName=function(){
                return this.fileName;
            }
            this.getFileContent=function(){
                return this.fileContent;
            }
        }
    var createNewXMLDoc = function (dataFormHistoryLocation, dataFormNumber, pcArchitecture) {//第一个参数为电子数据表格在数据表格数组中的起始位，第二个为电子数据表格的地址,XML以方案*.XML命名
        var XMLDoc = createXMLDoc();
        var declaration = XMLDoc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");
        XMLDoc.appendChild(declaration);
        var root = XMLDoc.createElement("machine");
        root.setAttribute("architecture", pcArchitecture);
        XMLDoc.appendChild(root);
        var device_description = XMLDoc.createElement("device_description");
        var IO_description = XMLDoc.createElement("IO_description");
        var IO_bus = XMLDoc.createElement("bus");
        var IO_device_io = XMLDoc.createElement("device_io");
        var IO_RT = XMLDoc.createElement("RT");
        IO_description.appendChild(IO_bus);
        IO_description.appendChild(IO_device_io);
        IO_description.appendChild(IO_RT);
        var config_description = XMLDoc.createElement("config_description");
        root.appendChild(device_description);
        root.appendChild(IO_description);
        root.appendChild(config_description);
        for (var i = 0; i < dataFormNumber; i++) {
            console.log("");
            console.log('in first');
            var dataFormArray = createEntityDataForm.dataFormArrayHistory[dataFormHistoryLocation].getDataFormArray();
            console.log(JSON.stringify(dataFormArray));
            var dataForm = dataFormArray[i];
            var device_uid = dataForm.deviceDescription.uid;
            var device_type = dataForm.getDeviceDescription().getTypeName();
            var device_entity = XMLDoc.createElement("device_entity");
            device_entity.setAttribute("type", device_type);
            device_entity.setAttribute("uid", device_uid);
            var device_Property_Array = dataForm.getDeviceDescription().getDevicePropertyArray();
            var dependence = XMLDoc.createElement("dependence");
            var description = XMLDoc.createElement("description");
            for (var j = 0; j < device_Property_Array.length; j++) {
                var name = device_Property_Array[j].getName();
                var value = device_Property_Array[j].getValue();
                var propertyNode = XMLDoc.createElement(name);
                var text_tmp_node = XMLDoc.createTextNode(value);
                propertyNode.appendChild(text_tmp_node);
                description.appendChild(propertyNode);
            }
            device_entity.appendChild(description);         //
            var IODescriptionArray = dataForm.getIODescriptionArray();
            if (IODescriptionArray.length === 0) {
                var text_tmp_node = XMLDoc.createTextNode("ROOT");
                dependence.appendChild(text_tmp_node);
                device_entity.appendChild(dependence);
                $(XMLDoc).find('device_description')[0].appendChild(device_entity);
                continue;
            }
            for (var j = 0; j < IODescriptionArray.length; j++) {
                console.log(IODescriptionArray.length);
                console.log('in second');
                var tagType;
                var IODescription = IODescriptionArray[j];
                var IOType = IODescription.getTypeName();
                var IOUid = IODescription.getUid();
                var IOChannel =IODescription.getChannel();
                var IO_Property_Array = IODescription.getIOPropertyArray();
                var RT_Property = IODescription.getRTDataTransferPriority();
                if (IOType === "ad" || IOType === "da") {
                    tagType = "device_io";
                }
                else if (IOType === "RT") {
                    tagType = "RT";
                }
                else {
                    tagType = "bus"
                }
                var isHaveChannel = false;
                if (IOChannel != null) {
                    isHaveChannel = true;
                }
                if (j === 0) {    //接口一，先为设备创建依赖
                    if (isHaveChannel === true) {
                        var text_tmp_node = XMLDoc.createTextNode(IOType + ":" + IOUid + ";" + "channel:" + IOChannel);
                        dependence.appendChild(text_tmp_node);
                    }
                    else {
                        var text_tmp_node = XMLDoc.createTextNode(IOType + ":" + IOUid);
                        dependence.appendChild(text_tmp_node);
                    }
                    device_entity.appendChild(dependence);
                    $(XMLDoc).find('device_description')[0].appendChild(device_entity);
                }
                var IOTagName = "io_" + IOType + "_entity";
                var isFindSameNode = false;
                $(XMLDoc).find(IOTagName + "[uid=" + IOUid + "][type=" + IOType + "]").each(function () {  //是否已经存在节点
                    if ($(this).attr("type") === "ad" || $(this).attr("type") === "ad"|| $(this).attr("type") === "RT") {
                        isFindSameNode = true;
                    }
                    if(isHaveChannel===true){
                        if($(this).attr("channel")===IOChannel){
                            isFindSameNode=true;
                        }
                    }
                    else{
                        if($(XMLDoc).find('io_'+IOType+'_entity'+'[uid='+IOUid+']').length!=0){
                            isFindSameNode=true;
                        }
                    }
                }); //创建一个新的接口_entity,在config中创建依赖
                if (isFindSameNode === false) {
                    var IO_entity = XMLDoc.createElement("io_" + IOType + "_entity");
                    IO_entity.setAttribute("type", IOType);
                    IO_entity.setAttribute("uid", IOUid);
                    if (isHaveChannel === false) {
                        var description = XMLDoc.createElement("description");
                        for (var k = 0; k < IO_Property_Array.length; k++) {
                            var name = IO_Property_Array[k].getName();
                            var value = IO_Property_Array[k].getValue();
                            var propertyNode = XMLDoc.createElement(name);
                            var text_tmp_node = XMLDoc.createTextNode(value);
                            propertyNode.appendChild(text_tmp_node);
                            description.appendChild(propertyNode);
                        }
                        IO_entity.appendChild(description);
                        if (IOType === "RT") {                                          //此接口为RT，增加tranData_description标签
                            var tranData_description = XMLDoc.createElement("tranData_description");
                            var send_priority = XMLDoc.createElement("send_priority");
                            var send_blockSize = XMLDoc.createElement("send_blockSize");
                            var receive_priority = XMLDoc.createElement("receive_priority");
                            var receive_blockSize = XMLDoc.createElement("receive_blockSize");
                            var device_uid = RT_Property.getDeviceUid();
                            var RT_device_Node1 = XMLDoc.createElement("device");
                            var RT_device_Node2 = XMLDoc.createElement("device");
                            var RT_device_Node3 = XMLDoc.createElement("device");
                            var RT_device_Node4 = XMLDoc.createElement("device");
                            RT_device_Node1.setAttribute("uid", device_uid);
                            RT_device_Node2.setAttribute("uid", device_uid);
                            RT_device_Node3.setAttribute("uid", device_uid);
                            RT_device_Node4.setAttribute("uid", device_uid);
                            var send_priority_value = RT_Property.getSendDataPriority();
                            var send_blockSize_value = RT_Property.getSendDataBlockSize();
                            var receive_priority_value = RT_Property.getReceiveDataPriority();
                            var receive_blockSize_value = RT_Property.getReceiveDataBlockSize();
                            var text_tmp_node = XMLDoc.createTextNode(send_priority_value);
                            RT_device_Node1.appendChild(text_tmp_node);
                            send_priority.appendChild(RT_device_Node1);
                            var text_tmp_node = XMLDoc.createTextNode(send_blockSize_value);
                            RT_device_Node2.appendChild(text_tmp_node);
                            send_blockSize.appendChild(RT_device_Node2);
                            var text_tmp_node = XMLDoc.createTextNode(receive_priority_value);
                            RT_device_Node3.appendChild(text_tmp_node);
                            receive_priority.appendChild(RT_device_Node3);
                            var text_tmp_node = XMLDoc.createTextNode(receive_blockSize_value);
                            RT_device_Node4.appendChild(text_tmp_node);
                            receive_blockSize.appendChild(RT_device_Node4);
                            tranData_description.appendChild(send_priority);
                            tranData_description.appendChild(send_blockSize);
                            tranData_description.appendChild(receive_priority);
                            tranData_description.appendChild(receive_blockSize);
                            IO_entity.appendChild(tranData_description);
                        }
                        $(XMLDoc).find('IO_description ' + tagType)[0].appendChild(IO_entity);
                    }
                    else if (isHaveChannel === true) {
                        var channel = XMLDoc.createElement("channel");
                        channel.setAttribute("uid", IOChannel);
                        var description = XMLDoc.createElement("description");
                        for (var k = 0; k < IO_Property_Array.length; k++) {
                            console.log('in third');
                            var name = IO_Property_Array[k].getName();
                            var value = IO_Property_Array[k].getValue();
                            var propertyNode = XMLDoc.createElement(name);
                            var text_tmp_node = XMLDoc.createTextNode(value);
                            propertyNode.appendChild(text_tmp_node);
                            description.appendChild(propertyNode);
                        }
                        channel.appendChild(description);
                        IO_entity.appendChild(channel);
                        $(XMLDoc).find('IO_description').find(tagType)[0].appendChild(IO_entity);
                    }
                    //cofig
                    var IO_config = XMLDoc.createElement("io_" + IOType + "_config");
                    IO_config.setAttribute("uid", IOUid);
                    if(IOChannel!=null){
                        IO_config.setAttribute("channel", IOChannel);
                    }
                    if (IODescriptionArray[j + 1] != undefined) {
                        var parentNode = XMLDoc.createElement("parent");
                        var parentNodeContent;
                        var next_IODescription = IODescriptionArray[j + 1];
                        var next_IOType = next_IODescription.getTypeName();
                        var next_IOUid = next_IODescription.getUid();
                        var next_IOChannel = next_IODescription.getChannel();
                        if (next_IOChannel === null) {
                            parentNodeContent = next_IOType + ":" + next_IOUid;
                        }
                        else {
                            parentNodeContent = next_IOType + ":" + next_IOUid + ";" + "channel:" + next_IOChannel;
                        }
                        var text_tmp_node = XMLDoc.createTextNode(parentNodeContent);
                        parentNode.appendChild(text_tmp_node);
                        IO_config.appendChild(parentNode);
                    }
                    else {
                        var parentNode = XMLDoc.createElement("parent");
                        var text_tmp_node = XMLDoc.createTextNode("ROOT");
                        parentNode.appendChild(text_tmp_node);
                        IO_config.appendChild(parentNode);
                    }
                    $(XMLDoc).find('config_description')[0].appendChild(IO_config);

                }


                else if (isFindSameNode === true) {
                    if (IOType === "RT") {     //加进去RT属性即可，不需要创建RT
                        var device_uid = RT_Property.getDeviceUid();
                        var RT_device_Node1 = XMLDoc.createElement("device");
                        var RT_device_Node2 = XMLDoc.createElement("device");
                        var RT_device_Node3 = XMLDoc.createElement("device");
                        var RT_device_Node4 = XMLDoc.createElement("device");
                        RT_device_Node1.setAttribute("uid", device_uid);
                        RT_device_Node2.setAttribute("uid", device_uid);
                        RT_device_Node3.setAttribute("uid", device_uid);
                        RT_device_Node4.setAttribute("uid", device_uid);
                        var send_priority_value = RT_Property.getSendDataPriority();
                        var send_blockSize_value = RT_Property.getSendDataBlockSize();
                        var receive_priority_value = RT_Property.getReceiveDataPriority();
                        var receive_blockSize_value = RT_Property.getReceiveDataBlockSize();
                        var text_tmp_node = XMLDoc.createTextNode(send_priority_value);
                        RT_device_Node1.appendChild(text_tmp_node);
                        var text_tmp_node = XMLDoc.createTextNode(send_blockSize_value);
                        RT_device_Node2.appendChild(text_tmp_node);
                        var text_tmp_node = XMLDoc.createTextNode(receive_priority_value);
                        RT_device_Node3.appendChild(text_tmp_node);
                        var text_tmp_node = XMLDoc.createTextNode(receive_blockSize_value);
                        RT_device_Node4.appendChild(text_tmp_node);
                        $(XMLDoc).find('io_RT_entity' + '[uid=' + IOUid + ']').find('tranData_description').find('send_priority')[0].appendChild(RT_device_Node1);
                        $(XMLDoc).find('io_RT_entity' + '[uid=' + IOUid + ']').find('tranData_description').find('send_blockSize')[0].appendChild(RT_device_Node2);
                        $(XMLDoc).find('io_RT_entity' + '[uid=' + IOUid + ']').find('tranData_description').find('receive_priority')[0].appendChild(RT_device_Node3);
                        $(XMLDoc).find('io_RT_entity' + '[uid=' + IOUid + ']').find('tranData_description').find('receive_blockSize')[0].appendChild(RT_device_Node4);
                    }
                }

            }
        }
        console.log('create new XML success');
        return XMLDoc;
    }
    var createXMLDoc = function () {
        try {
            var XMLDoc = new ActiveXObject("Microsoft.XMLDOM");
        } catch (e) {
            try {
                var XMLDoc = document.implementation.createDocument("", "", null);
            } catch (e) {
                alert(e.message);
            }
        }
        return XMLDoc;
    }
    var serializeXMLDoc = function (XMLDoc) {
        var text;
        try {
            text = (new XMLSerializer()).serializeToString(XMLDoc);
        } catch (e) {
            text = XMLDoc.xml;
        }
        return text;
    }
    return {
        createNewXMLDoc: createNewXMLDoc,
        serializeXMLDoc: serializeXMLDoc,
        createXMLFileNode:createXMLFileNode,
        XMLFileHistoryArray:XMLFileHistoryArray
    }
});