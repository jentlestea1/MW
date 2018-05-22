/**
 * Created by wangshaobo_ on 2017/7/30.
 */
define(['js/createModel', 'js/createEntityDataForm', 'js/buildXMLConfigFile', 'js/resourceInteract'], function (createModel, createEntityDataForm, buildXMLConfigFile, resourceInteract) {
    var descriptionArray = [];
    var projectUid = "1";
    var XMLFileUid = "1";
    var configListHistory = [],
        configListHistoryNode = function () {
            this.html = null;
            this.getHtml = function () {
                return this.html;
            }
        }
    var viewInit = function () {
        $('#cpu_confirm').on('click', function () {
            createCpuEntity();
        });
        $('#addPortIcon').on('click', function () {
            var div = $('<div class="form-group" tag="portAddDiv"></div>');
            div.append($('#portSelectDiv').html());
            var divCount = $('#section7').find('div[tag="portAddDiv"]').length + 1;
            div.find('label').html('端口' + divCount);
            $('#addPort').before(div);
        });
        $('#selectXMLFile_confirm').on('click', function (e) {
            var XMLListNum = parseInt($('#XMLFile_select').find('option:selected').attr("value")) - 1;
            console.log(XMLListNum);
            console.log(buildXMLConfigFile.XMLFileHistoryArray.length);
            var fileName = buildXMLConfigFile.XMLFileHistoryArray[XMLListNum].getFileName();
            var XMLFile = buildXMLConfigFile.XMLFileHistoryArray[XMLListNum].getFileContent();
            resourceInteract.loadXML(e, XMLFile, fileName);
        });
        $('#loadXMLFile').on('click', function () {
            $('#XMLFile_select_modal').modal('show');
        });
        $('#createXML').on('click', function () {
            var location = parseInt($('#XML_select_scheme').find('option:selected').attr("value")) - 1;
            var dataFormNumber = createEntityDataForm.dataFormArrayHistory[location].getDataFormArray().length;
            var projectName = $('#XML_select_scheme').find('option:selected').html();
            //console.log(location+"|"+dataFormNumber+"|"+projectName);
            $('#loadProgress_XML').attr("style", "z-index:9999 !important;position: absolute;padding-left: 360px;padding-top: 100px;display: block");
            //createEntityDataForm.checkDataFormArrayContent(location,dataFormNumber);
            var XMLDoc = createXMLDoc(location, dataFormNumber, projectName);
            var XMLDocSerial = buildXMLConfigFile.serializeXMLDoc(XMLDoc);
            var XMLFileNode = new buildXMLConfigFile.createXMLFileNode();
            XMLFileNode.fileName = projectName;
            XMLFileNode.fileContent = XMLDocSerial;
            buildXMLConfigFile.XMLFileHistoryArray.push(XMLFileNode);
            var option = $('<option></option>');
            option.attr("value", XMLFileUid);
            option.html(projectName + ".xml");
            $('#XMLFile_select').append(option);
            XMLFileUid++;
            setTimeout(" $('#loadProgress_XML').attr('style','position: absolute;padding-left: 380px;padding-top: 150px;display: none');", 600);

        });
        $('#buildXML').on('click', function () {
            $('#XML_select_scheme').find('option').remove();
            $('#XML_select_scheme').html($('#select_scheme').html());
            $('#XML_select_scheme').find('option[value="0"]').remove();
            $('#XML_select_scheme').find('option[value!="0"]').attr("selected", false);
            $('#XML_select_scheme').find('option[value="0"]').attr("selected", true);
        });
        $('#createXML_selScheme').on('click', function () {
            $('#XML_selectScheme_modal').modal('show');
        });
        $('#buildScheme').on('click', function () {
            //已经存在的方案，不需要新生成

            if ($('#configList tbody').html() === "")return;
            if ($('#configList tbody td[name!=device]').html() === "")return;
            //注意导数第二个为RT且倒数第一个不为1553b提示选择总线类型，return
            var find = false;
            var projectListNum;
            var projectExisted = false;
            $('#configList tbody td').each(function () {
                if ($(this).find('option:selected').attr("name") === "RT") {
                    if ($(this).next().html() != 0 && $(this).next().find('option:selected').attr("name") != "1553b") {
                        find = true;
                        $('#tip').find('h3').eq(0).attr("style", "font-weight: bolder;display:none");
                        $('#tip').find('h3').eq(1).attr("style", "font-weight: bolder;display:block");
                        $(this).next().attr("style", "background-color:red");
                    }
                }
            });
            if (find === true) {
                $('#configTip').modal('show');
                return;
            }
            $('#section5').attr("style", "background-color: rgba(47,79,79,0.7)");
            $('#loadProgress').attr("style", "position: absolute;padding-left: 380px;padding-top: 150px;display: block");
            createEntityDataForm.clearDataFormArray();
            if ($('#select_scheme').find('option:selected').attr("value") != "0") {
                projectListNum = $('#select_scheme').find('option:selected').attr("value") - 1;
                projectExisted = true;
                //console.log(JSON.stringify(createEntityDataForm.RTTransferArrayHistory[projectListNum]));
                var RTTransferArray = createEntityDataForm.RTTransferArrayHistory[projectListNum];
                for (var i = 0; i < RTTransferArray.getRTTransferArray().length; i++) {
                    createEntityDataForm.RTTransferArray.push(RTTransferArray.getRTTransferArray()[i]);
                }
            }
            //console.log(JSON.stringify(createEntityDataForm.RTTransferArrayHistory));
            //console.log(JSON.stringify(createEntityDataForm.RTTransferArray));
            createEntityDataFormArray(projectExisted, projectListNum);
            console.log('end create');
            $('#configModelDesk tbody td').find('option:selected[name="selectIO"]').parent().parent().html('');
            $('#configModelDesk tbody td').find('option').not('option:selected').remove();
            var RTTransferArrayObject = new createEntityDataForm.createRTTransferArray;
            arrayDeepCopy(RTTransferArrayObject.RTTransferArray, createEntityDataForm.RTTransferArray);
            if (projectExisted === false) {
                createEntityDataForm.RTTransferArrayHistory.push(RTTransferArrayObject);
                var option = $('<option></option>');
                option.html("方案" + projectUid);
                projectUid++;
                $('#select_scheme').append(option);
                option.attr("selected", true);
                reSetOptionValue();
                var configHistory = new configListHistoryNode;
                var html = $('#configList tbody').html();
                configHistory.html = html;
                configListHistory.push(configHistory);
            }
            else {
                createEntityDataForm.RTTransferArrayHistory[projectListNum] = RTTransferArrayObject;
                var configHistory = new configListHistoryNode;
                var html = $('#configList tbody').html();
                configHistory.html = html;
                configListHistory[projectListNum] = configHistory;
            }
            createEntityDataForm.clearRTTransferArray();
            console.log('数据表格数量:' + createEntityDataForm.dataFormArray.length);
            console.log('工程数量:' + createEntityDataForm.dataFormArrayHistory.length);
            setTimeout(" $('#loadProgress').attr('style','position: absolute;padding-left: 380px;padding-top: 150px;display: none');" +
                "$('#section5').removeAttr('style');", 800);
            //$('#loadProgress').attr('style','position: absolute;padding-left: 380px;padding-top: 150px;display: none');
            // $('#section5').bind("click");
            //$('#section5').removeAttr('style');
            // $('#loadProgress').attr("style","display: none");
        });
        $('#select_scheme').change(function () {
            //console.log('in');
            $('#buildScheme').attr("disabled", false);
            var listNumber = $(this).find('option:selected').attr("value");
            if (listNumber === "0") {
                clearConfigList();
                loadDeviceToConfigList();
            }
            if (configListHistory[parseInt(listNumber) - 1] != undefined) {
                var html = configListHistory[parseInt(listNumber) - 1].getHtml();
                $('#configList tbody').html(html);
            }
            setIOSelectOption();
            //console.log(html);
            $('#configList tbody td[name="device"]').each(function () {
                var a = -1;
                for (var i = 0; i < createModel.deviceArray.length; i++) {
                    if ($(this).attr("uid") === createModel.deviceArray[i].getUid()) {
                        a = 1;
                    }
                }
                if (a === -1) {
                    $('#tip').find('h3').eq(0).attr("style", "font-weight: bolder;display:block");
                    $('#tip').find('h3').eq(1).attr("style", "font-weight: bolder;display:none");
                    $('#configTip').modal('show');
                    $('#buildScheme').attr("disabled", true);
                }
            });
        });
        $('#deleteScheme').on('click', function () {
            $('#configList tbody td[name!="device"]').html('');
            var c = $('#select_scheme option:selected[value!="0"]').attr("value");
            var a = parseInt(c) - 1;
            configListHistory.splice(a, 1);
            createEntityDataForm.dataFormArrayHistory.splice(a, 1);
            createEntityDataForm.RTTransferArrayHistory.splice(a, 1);
            //console.log(configListHistory.length);
            $('#select_scheme').find('option:selected[value!="0"]').remove();
            reSetOptionValue();
        });
        $('#setPriorityAndBlockSize').on('click', function () {
            if ($('#inputPriorityAndBlockSize').find('.form-group').eq(2).attr("style") === "display:none") {
                if ($('#inputPriorityAndBlockSize input').eq(0).val() != "") {
                    $('#inputPriorityAndBlockSize').modal('hide');
                    //
                    var RTTransferNode = new createEntityDataForm.createRTTransferNode;
                    RTTransferNode.deviceUid = $('#dev_uid_label').html();
                    RTTransferNode.receiveDataBlockSize = $('#inputPriorityAndBlockSize input').eq(0).val();
                    RTTransferNode.receiveDataPriority = $('#inputPriorityAndBlockSize select').eq(0).find('option:selected').text();
                    createEntityDataForm.RTTransferArray.push(RTTransferNode);
                }
                else {
                    $('#inputPriorityAndBlockSize input').eq(0).attr("style", "width: 200px;border-color: red");
                }
            }
            else if ($('#inputPriorityAndBlockSize').find('.form-group').eq(0).attr("style") === "display:none") {
                if ($('#inputPriorityAndBlockSize input').eq(1).val() != "") {
                    $('#inputPriorityAndBlockSize').modal('hide');
                    //
                    var RTTransferNode = new createEntityDataForm.createRTTransferNode;
                    RTTransferNode.deviceUid = $('#dev_uid_label').html();
                    RTTransferNode.sendDataBlockSize = $('#inputPriorityAndBlockSize input').eq(1).val();
                    RTTransferNode.sendDataPriority = $('#inputPriorityAndBlockSize select').eq(1).find('option:selected').text();
                    createEntityDataForm.RTTransferArray.push(RTTransferNode);
                }
                else {
                    $('#inputPriorityAndBlockSize input').eq(1).attr("style", "width: 200px;border-color: red");
                }
            }
            else {
                if ($('#inputPriorityAndBlockSize input').eq(0).val() != "" && $('#inputPriorityAndBlockSize input').eq(1).val() != "") {
                    $('#inputPriorityAndBlockSize').modal('hide');
                    //-》保存
                    var RTTransferNode = new createEntityDataForm.createRTTransferNode;
                    RTTransferNode.deviceUid = $('#dev_uid_label').html();
                    RTTransferNode.receiveDataBlockSize = $('#inputPriorityAndBlockSize input').eq(0).val();
                    RTTransferNode.receiveDataPriority = $('#inputPriorityAndBlockSize select').eq(0).find('option:selected').text();
                    RTTransferNode.sendDataBlockSize = $('#inputPriorityAndBlockSize input').eq(1).val();
                    RTTransferNode.sendDataPriority = $('#inputPriorityAndBlockSize select').eq(1).find('option:selected').text();
                    createEntityDataForm.RTTransferArray.push(RTTransferNode);
                }
                else {
                    if ($('#inputPriorityAndBlockSize input').eq(0).val() === "") {
                        $('#inputPriorityAndBlockSize input').eq(0).attr("style", "width: 200px;border-color: red");
                    }
                    if ($('#inputPriorityAndBlockSize input').eq(1).val() === "") {
                        $('#inputPriorityAndBlockSize input').eq(1).attr("style", "width: 200px;border-color: red");
                    }
                }
            }

        });
        $('#inputPriorityAndBlockSize input').eq(0).on('keydown', function () {
            $('#inputPriorityAndBlockSize input').eq(0).attr("style", "width: 200px;");
        });
        $('#inputPriorityAndBlockSize input').eq(1).on('keydown', function () {
            $('#inputPriorityAndBlockSize input').eq(1).attr("style", "width: 200px;");
        });
        $('#refreshConfigList').on('click', function () {
            clearAllIOSelectOptions();
        });
        //$('#configList').click(function () {
        //setIOSelectOption();
        // });
        $('div.accordion-heading').click(function () {
            $('#toggled').removeAttr('id');
            $(this).attr('id', 'toggled');
        });
        $('#addDeviceOrIO').on('click', function () {
            $(this).parent().attr("class", "list-group-item");
        });
        $('#toVisualMode').on('click', function () {
            $(this).parent().attr("class", "list-group-item");
            $('body').attr("background", "img/vi_bg1.jpg");
        });
        $('#returnToConsoleMode').on('click', function () {
            $('body').attr("background", "img/bg_satellite.jpg");
        });
        $('#configIO').on('click', function () {
            $(this).parent().attr("class", "list-group-item");
            clearConfigList();
            loadDeviceToConfigList();
            clearListControlOptions();
            LoadListControlOptions();
            setIOSelectOption();
            $('#buildScheme').attr("disabled", false);
            $('#select_scheme').find('option[value!="0"]').attr("selected", false);
            $('#select_scheme').find('option[value="0"]').attr("selected", true);
            //configDeskToFullScreen();
        });
        $('#buildXML').on('click', function () {
            $(this).parent().attr("class", "list-group-item");
        });
        $('#myNavbar a').eq(0).on('click', function () {
            transferContentView('device');
        });
        $('#myNavbar a').eq(1).on('click', function () {
            transferContentView('bus');
        });
        $('#myNavbar a').eq(2).on('click', function () {
            transferContentView('device_io');
        });
        $('#myNavbar a').eq(3).on('click', function () {
            transferContentView('RT');
        });
        $('#myNavbar a').eq(4).on('click', function () {
            transferContentView('cpu');
        });
        $('#createList button').eq(0).on('click', function () {
            returnCreateView('device');
        });
        $('#IO_createList button').eq(0).on('click', function () {
            returnCreateView('IO');
        });
        $('#cpu_createList button').eq(0).on('click', function () {
            returnCreateView('cpu');
        });
        $('#create .modal-footer button').on('click', function () {
            //clearFormContent('device');
        });
        $('#IO_create .modal-footer button').on('click', function () {
            //clearFormContent('IO');
        });
        $("#confirm").on('click', function () {
            createDeviceEntity();
            console.log('device num:' + createModel.deviceArray.length);
        });
        $("#IO_confirm").on('click', function () {
            createIOEntity();
            console.log('IO num:' + (createModel.RTArray.length + createModel.deviceIOArray.length + createModel.busArray.length));
        });
        $('#view').on('click', function () {
            viewEntityList('device');
        });
        $('#IO_view').on('click', function () {
            viewEntityList('IO');
        });
        $('#cpu_view').on('click', function () {
            viewEntityList('cpu');
        });
        $('#createList button').eq(1).on('click', function () {
            deleteEntity('device');
        });
        $('#IO_createList button').eq(1).on('click', function () {
            deleteEntity('io');
        });
        $('#cpu_createList button').eq(1).on('click', function () {
            deleteEntity('cpu');
        });
        $('textarea').each(function () {
            $(this).on('keypress', function (e) {
                var ecode = e.keyCode;
                var ColonVisit = true;
                //console.log(ecode);
                //if((ecode<188||ecode>190)&&(ecode<65||ecode>105)){
                //     alert('不能输入除数字,字母,":",";","_"之外的字符');
                // }
                var str = $(this).val();
                for (var i = str.length - 1; i >= 0; i--) {
                    if (str[i] === ':') {
                        ColonVisit = false;
                        break;
                    }//{alert('please input as **:**;**:** form');return;}
                    else if (str[i] === ';') {
                        ColonVisit = true;
                        break;
                    }
                }
                if ((ecode === 58 && ColonVisit === false) || (ecode === 59 && ColonVisit === true)) {
                    alert('请以属性名:属性值;属性名:属性值的格式输入,注意":"为半角字符');
                    return;
                }
            });
        });
    }


    var createDeviceTrRow = function (uid, type, model, dataSize) {
        if (uid === "" || type === "" || model === "" || dataSize === "") {
            $('#create  h3').eq(2).attr("style", "color: #080808;font-weight: bolder;display: block");
            $('#create  h3').eq(0).attr("style", "color: #080808;font-weight: bolder;display: none");
            $('#create  h3').eq(1).attr("style", "color: #080808;font-weight: bolder;display: none");
            return false;
        }
        if ($("#createList tbody").find("a").html() == uid) {
            $('#create  h3').eq(1).attr("style", "color: #080808;font-weight: bolder;display: block");
            $('#create  h3').eq(0).attr("style", "color: #080808;font-weight: bolder;display: none");
            $('#create  h3').eq(2).attr("style", "color: #080808;font-weight: bolder;display: none");
            return false;
        }
        $(' #create  h3').eq(0).attr("style", "color: #080808;font-weight: bolder;display: block");
        $(' #create  h3').eq(1).attr("style", "color: #080808;font-weight: bolder;display: none");
        $(' #create  h3').eq(2).attr("style", "color: #080808;font-weight: bolder;display: none");
        var tr = $("<tr></tr>");
        var checkboxtd = $("<td></td>");
        var checkbox = $("<input />");
        checkbox.attr("type", "checkbox");
        checkboxtd.append(checkbox);
        tr.append(checkboxtd);
        var idtd = $("<td></td>");
        var a = $("<a></a>");
        a.append(uid);
        //console.log('deviceNode.getUid():'+id.innerHTML);
        a.attr("href", "#");
        a.attr("style", "color:black");
        idtd.append(a);
        tr.append(idtd);
        var typetd = $("<td></td>");
        typetd.append(type);
        tr.append(typetd);
        var modeltd = $("<td></td>");
        modeltd.append(model);
        tr.append(modeltd);
        var dataSizetd = $("<td></td>");
        dataSizetd.append(dataSize);
        tr.append(dataSizetd);
        $('#createList tbody').append(tr);
        return true;
    }
    var createIOTrRow = function (uid, type, subAddr) {
        if (uid === "" || type === "") {
            $('#IO_create  h3').eq(2).attr("style", "color: #080808;font-weight: bolder;display: block");
            $('#IO_create  h3').eq(0).attr("style", "color: #080808;font-weight: bolder;display: none");
            $('#IO_create  h3').eq(1).attr("style", "color: #080808;font-weight: bolder;display: none");
            return false;
        }
        var judge = true;
        $("#IO_createList tbody tr").each(function () {
            // console.log($(this).find('a').html()+'|'+$(this).find('#type').html());
            if (subAddr === "") {
                if ($(this).find('a').html() === uid && $(this).find('td[name="type"]').html() === type) {
                    $('#IO_create  h3').eq(1).attr("style", "color: #080808;font-weight: bolder;display: block");
                    $('#IO_create  h3').eq(0).attr("style", "color: #080808;font-weight: bolder;display: none");
                    $('#IO_create  h3').eq(2).attr("style", "color: #080808;font-weight: bolder;display: none");
                    judge = false;
                }
            }
            else {
                if (($(this).find('a').html() === uid && $(this).find('td[name="type"]').html() === type && $(this).find('td[name="subAddr"]').html() === subAddr)) {
                    $('#IO_create  h3').eq(1).attr("style", "color: #080808;font-weight: bolder;display: block");
                    $('#IO_create  h3').eq(0).attr("style", "color: #080808;font-weight: bolder;display: none");
                    $('#IO_create  h3').eq(2).attr("style", "color: #080808;font-weight: bolder;display: none");
                    judge = false;
                }
            }
        });
        if (judge === false)return false;
        $(' #IO_create  h3').eq(0).attr("style", "color: #080808;font-weight: bolder;display: block");
        $(' #IO_create  h3').eq(1).attr("style", "color: #080808;font-weight: bolder;display: none");
        $(' #IO_create  h3').eq(2).attr("style", "color: #080808;font-weight: bolder;display: none");
        var tr = $("<tr></tr>");
        var checkboxtd = $("<td></td>");
        var checkbox = $("<input />");
        checkbox.attr("type", "checkbox");
        checkboxtd.append(checkbox);
        tr.append(checkboxtd);
        var idtd = $("<td></td>");
        var a = $("<a></a>");
        a.append(uid);
        //console.log('deviceNode.getUid():'+id.innerHTML);
        a.attr("href", "#");
        a.attr("style", "color:black");
        idtd.append(a);
        tr.append(idtd);
        var typetd = $("<td></td>");
        typetd.append(type);
        typetd.attr("name", "type");
        tr.append(typetd);
        var subAddrtd = $("<td></td>");
        subAddrtd.attr("name", "subAddr");
        subAddrtd.append(subAddr);
        tr.append(subAddrtd);
        $('#IO_createList tbody').append(tr);
        return true;
    }
    var createCpuTrRow = function (uid, model) {
        if (uid === "" || model === "") {
            $('#cpu_create  h3').eq(2).attr("style", "color: #080808;font-weight: bolder;display: block");
            $('#cpu_create  h3').eq(0).attr("style", "color: #080808;font-weight: bolder;display: none");
            $('#cpu_create  h3').eq(1).attr("style", "color: #080808;font-weight: bolder;display: none");
            return false;
        }
        var judge = true;
        $("#cpu_createList tbody tr").each(function () {
            // console.log($(this).find('a').html()+'|'+$(this).find('#type').html());
            if ($(this).find('a').html() === uid) {
                $('#cpu_create  h3').eq(1).attr("style", "color: #080808;font-weight: bolder;display: block");
                $('#cpu_create  h3').eq(0).attr("style", "color: #080808;font-weight: bolder;display: none");
                $('#cpu_create  h3').eq(2).attr("style", "color: #080808;font-weight: bolder;display: none");
                judge = false;
            }

        });
        if (judge === false)return false;
        $('#cpu_create  h3').eq(0).attr("style", "color: #080808;font-weight: bolder;display: block");
        $('#cpu_create  h3').eq(1).attr("style", "color: #080808;font-weight: bolder;display: none");
        $('#cpu_create  h3').eq(2).attr("style", "color: #080808;font-weight: bolder;display: none");
        var tr = $("<tr></tr>");
        var checkboxtd = $("<td></td>");
        var checkbox = $("<input />");
        checkbox.attr("type", "checkbox");
        checkboxtd.append(checkbox);
        tr.append(checkboxtd);
        var idtd = $("<td></td>");
        var a = $("<a></a>");
        a.append(uid);
        //console.log('deviceNode.getUid():'+id.innerHTML);
        a.attr("href", "#");
        a.attr("style", "color:black");
        idtd.append(a);
        tr.append(idtd);
        var modeltd = $("<td></td>");
        modeltd.append(model);
        modeltd.attr("name", "model");
        tr.append(modeltd);
        $('#cpu_createList tbody').append(tr);
        return true;
    }
    var createDeviceEntity = function () {
        var uid = $('#id').val(),
            type = $('#type').val(),
            model = $('#model').val(),
            dataSize = $('#data_size').val();
        var isSuccess = createDeviceTrRow(uid, type, model, dataSize);
        if (isSuccess === true) {
            parseDescriptionContent("device");
            createModel.createNewDeviceModel(uid, type, model, dataSize, descriptionArray);
        }
    }
    var createIOEntity = function () {
        var uid = $('#IO_id').val(),
            type = $('#IO_type').find('option:selected').text(),
            subAddr = $('#IO_subAddr').val();
        console.log(subAddr);
        var isSuccess = createIOTrRow(uid, type, subAddr);
        if (isSuccess === true) {
            parseDescriptionContent('io');
            createModel.createNewIOModel(uid, type, subAddr, descriptionArray);
        }
    }
    var createCpuEntity = function () {
        var count = 0;
        var portArray = [];
        var uid = $('#section7').find('input').eq(0).val();
        var model = $('#section7').find('input').eq(1).val();
        $('#section7').find('div[tag="portAddDiv"]').each(function () {
            count++;
            var name = $(this).find('select option:selected').eq(0).text();
            var supportIO = $(this).find('select option:selected').eq(1).text();
            var portArrayNode = new createModel.createPortArrayNode;
            portArrayNode.uid = count;
            portArrayNode.name = name;
            portArrayNode.supportIO = supportIO;
            portArray.push(portArrayNode);
        });
        if (createCpuTrRow(uid, model) === true) {
            createModel.createNewCpuUnitModel(uid, model, portArray);
        }
    }
    var deleteEntity = function (type) {
        var listSelect;
        if (type === 'device')listSelect = '#createList';
        else if (type === 'cpu') listSelect = '#cpu_createList';
        else listSelect = '#IO_createList';
        $(listSelect + ' tbody tr').each(function () {
                //$(this).find("td:first").find("input")
                if ($(this).find("input").is(':checked')) {
                    $(this).fadeOut(500, function () {
                        var uid = $(this).find('a').html();
                        if (type === 'device')createModel.deleteDeviceModel(uid);
                        else if (type === 'cpu')createModel.deleteCpuUnitModel(uid);
                        else {
                            var type_subType_tmp = $(this).find('td[name="type"]').html();
                            createModel.deleteIOModel(type_subType_tmp, uid);
                        }
                        $(this).remove();
                    });
                }
            }
        );
    }
    var parseDescriptionContent = function (type) {
        descriptionArray = [];
        var str;
        if (type === "device")str = $('#device_content textarea').val();
        else str = $('#IO_content textarea').val();
        var arr = str.split(';');
        for (var i = 0; i < arr.length; i++) {
            var description_node = new createModel.createDescriptionNode;
            var arr_tmp = arr[i].split(':');
            if (arr_tmp[0] === "" || arr_tmp[1] === "" || arr_tmp[0] === undefined || arr_tmp[1] === undefined)continue;
            description_node.name = arr_tmp[0];
            description_node.value = arr_tmp[1];
            descriptionArray.push(description_node);
        }
    }

    var clearFormContent = function (type) {
        var select;
        if (type === 'device')select = '#create';
        else select = '#IO_create';
        $(select + ' form input').val("");
        $(select + ' form textarea').val("");
    }
    var viewEntityList = function (type) {
        if (type === 'device') {
            $('#create').attr("style", "display:none");
            $('#createList').attr("style", "display:block");
        }
        else if (type === 'cpu') {
            $('#cpu_create').attr("style", "display:none");
            $('#cpu_createList').attr("style", "display:block");
        }
        else {
            $('#IO_create').attr("style", "display:none");
            $('#IO_createList').attr("style", "display:block");
        }
    }
    var returnCreateView = function (type) {
        if (type === 'device') {
            $('#create').attr("style", "display:block");
            $('#createList').attr("style", "display:none");
        }
        else if (type === 'cpu') {
            $('#cpu_create').attr("style", "display:block");
            $('#cpu_createList').attr("style", "display:none");
        }
        else {
            $('#IO_create').attr("style", "display:block");
            $('#IO_createList').attr("style", "display:none");
        }
    }
    var loadDeviceToConfigList = function () {
        for (var i = 0; i < createModel.deviceArray.length; i++) {
            var uid = createModel.deviceArray[i].getUid();
            var type = createModel.deviceArray[i].getType();
            //var model=createModel.deviceArray[i].getModel();
            //var dataSize=createModel.deviceArray[i].getDataSize();
            //createDeviceTrRow(uid,type,model,dataSize);
            createConfigTrRow(type, uid);
        }
    }
    var clearConfigList = function () {
        $('#configList tbody').empty();
    }
    var createConfigTrRow = function (device_type, device_uid) {
        var tr = $('<tr></tr>');
        var device_td = $('<td></td>');
        var device_display = device_type + '<br>' + device_uid;
        device_td.append(device_display);
        device_td.attr("name", "device");
        device_td.attr("type", device_type);
        device_td.attr("uid", device_uid);
        tr.append(device_td);
        for (var i = 0; i < 6; i++) {
            var td = $('<td></td>');
            td.attr("style", "background-color:rgba(255,69,0,0.2)");
            tr.append(td);
        }
        $('#configList tbody').append(tr);
    }
    var transferContentView = function (select) {
        if (select !== 'device' && select != 'cpu') {
            clearFormContent('IO');
            $('#IO_content input').eq(0).attr("placeholder", "输入接口uid，如001");
            $('#IO_content input').eq(2).attr("placeholder", "输入子地址，表示通道号或路数，可以为空");
            $('#IO_content textarea').attr("placeholder", "接口属性，以属性名:属性值;属性名:属性值的格式输入哦,注意':'为半角字符");
        }
        if (select !== 'device' && select !== 'cpu') {
            $('#section1').attr("style", "display:none");
            $('#section7').attr("style", "display:none");
            $('#IO_content').parent().attr("style", "display:block");
        }
        switch (select) {
            case "device":
                $('#section1 input').eq(0).val("");
                $('#section1 input').eq(1).val("");
                $('#section1 input').eq(2).val("");
                $('#section1 input').eq(3).val("");
                $('#section1 textarea').val("");
                $('#section1').attr("style", "display:block");
                $('#section7').attr("style", "display:none");
                $('#IO_content').parent().attr("style", "display:none");
                break;
            case "cpu":
                $('#section7 input').eq(0).val("");
                $('#section7 input').eq(1).val("");
                $('#section7').find('div[tag="portAddDiv"]').remove();
                $('#section1').attr("style", "display:none");
                $('#section7').attr("style", "display:block");
                $('#IO_content').parent().attr("style", "display:none");
                break;
            case "bus":
                $('#IO_content').parent().attr("id", "section2");
                $('#IO_content input').eq(1).attr("placeholder", "请输入总线接口通道号/路数");
                $('#IO_type').find('optgroup').eq(0).attr("style", "display:block");
                $('#IO_type').find('optgroup').eq(1).attr("style", "display:none");
                $('#IO_type').find('optgroup').eq(2).attr("style", "display:none");
                $('#IO_type').find('option[value="1"]').attr("selected", true);
                $('#IO_type').find('option[value!="1"]').attr("selected", false);
                //$('#IO_type').attr("list", "list_bus");
                $('#IO_content div .form-group').eq(2).attr("style", "display:block");
                break;
            case "device_io":
                $('#IO_content').parent().attr("id", "section3");
                $('#IO_content input').eq(1).attr("placeholder", "选择设备接口类型");
                $('#IO_type').find('optgroup').eq(0).attr("style", "display:none");
                $('#IO_type').find('optgroup').eq(1).attr("style", "display:block");
                $('#IO_type').find('optgroup').eq(2).attr("style", "display:none");
                $('#IO_type').find('option[value="7"]').attr("selected", true);
                $('#IO_type').find('option[value!="7"]').attr("selected", false);
                //$('#IO_type').attr("list", "list_deviceIO");
                $('#IO_content div .form-group').eq(2).attr("style", "display:none");
                break;
            case "RT":
                $('#IO_content').parent().attr("id", "section4");
                $('#IO_content input').eq(1).attr("placeholder", "选择RT接口类型");
                $('#IO_type').find('optgroup').eq(0).attr("style", "display:none");
                $('#IO_type').find('optgroup').eq(1).attr("style", "display:none");
                $('#IO_type').find('optgroup').eq(2).attr("style", "display:block");
                $('#IO_type').find('option[value="9"]').attr("selected", true);
                $('#IO_type').find('option[value!="9"]').attr("selected", false);
                //$('#IO_type').attr("list", "list_RT");
                $('#IO_content div .form-group').eq(2).attr("style", "display:none");
                break;
            default :
                break;
        }
    }
    var clearListControlOptions = function () {
        $('#listControl select option[name!="selectIO"]').remove();
    }
    var LoadListControlOptions = function () {
        //导入所有接口数据，option的文本中添加“类型名 uid”，option添加属性“ name=“类型名 uid=“uid” ”
        var select = $('#listControl select');
        for (var i = 0; i < createModel.busArray.length; i++) {
            var option = $('<option></option>');
            if (createModel.busArray[i].getSubAddr() != "") {
                option.html(createModel.busArray[i].getType() + ' ' + createModel.busArray[i].getUid() + ';channel:' + createModel.busArray[i].getSubAddr());
                option.attr("channel", createModel.busArray[i].getSubAddr());
            }
            else {
                option.html(createModel.busArray[i].getType() + ' ' + createModel.busArray[i].getUid());
            }
            option.attr("name", createModel.busArray[i].getType());
            option.attr("uid", createModel.busArray[i].getUid());
            option.attr("type", "bus");
            console.log(option.attr("name") + "|" + option.attr("uid") + "|" + option.attr("channel") + "|" + option.html());
            select.append(option);
        }
        for (var i = 0; i < createModel.deviceIOArray.length; i++) {
            var option = $('<option></option>');
            option.html(createModel.deviceIOArray[i].getType() + ' ' + createModel.deviceIOArray[i].getUid());
            option.attr("name", createModel.deviceIOArray[i].getType());
            option.attr("uid", createModel.deviceIOArray[i].getUid());
            option.attr("type", "deviceIO");
            select.append(option);
        }
        for (var i = 0; i < createModel.RTArray.length; i++) {
            var option = $('<option></option>');
            option.html(createModel.RTArray[i].getType() + ' ' + createModel.RTArray[i].getUid());
            option.attr("name", createModel.RTArray[i].getType());
            option.attr("uid", createModel.RTArray[i].getUid());
            option.attr("type", "RT");
            select.append(option);
        }
        for (var i = 0; i < createModel.cpuUnitArray.length; i++) {
            var option = $('<option name="ROOT" uid=' + createModel.cpuUnitArray[i].getUid() + '></option>');
            option.html("ROOT" + ' ' + createModel.cpuUnitArray[i].getUid());
            select.append(option);
        }
        console.log('load listControl options success');
    }
    var setIOSelectOption = function () {
        //console.log(event.srcElement.innerHTML+'|'+event.srcElement.parentNode.children[0].innerHTML);
        $('#configModelDesk tbody td').each(
            function () {
                $(this).click(function (e) {
                    if (($(e.target)[0].tagName != "TD" && $(e.target)[0].tagName != "SELECT") || $(e.target).attr("name") === "device" ||
                        ($(e.target).prev().html() === "" && $(e.target).prev()[0].tagName === "TD")) {
                        //console.log($(e.target)[0].tagName);
                        return;
                    }
                    //if ($(e.target).attr('m_position') === "0")return;
                    //{第一接口不能为1553b
                    //    var select=$('<select></select>');
                    //    select.append(options.not("[name='1553b']"));
                    //     $(e.target).append(select);
                    //  }
                    //  else{ //同一个接口一行不能出现两次


                    //   }
                    //if($(e.target).attr('m_position')==="")return;
                    //else {
                    if ($(e.target)[0].tagName === "TD") {
                        if ($(e.target).html() != "")return;
                        // console.log($('#listControl').html());
                        //$(e.target).html($('#listControl').html());
                        // console.log($(e.target).prev().attr("name"));
                        if ($(e.target).prev().find('option:selected').attr("name") === "ROOT") {
                            return;
                        }
                        if ($(e.target).parent().parent().find('option:selected[name="selectIO"]').length != 0) {
                            return;
                        }
                        $('#configList').find('option').not('option:selected').remove();
                        $(e.target).html($('#listControl').html());
                        if ($(e.target).prev().attr("name") === "device") {
                            $(e.target).find('option[name="1553b"],[name="ROOT"]').remove();
                        }
                        else if ($(e.target).prev().attr("name") != "device") {
                            if ($(e.target).prev().find('option:selected').attr("name") === "RT") {
                                $(e.target).find('option').not('[name="1553b"],[name="selectIO"]').remove();
                                $('#inputPriorityAndBlockSize').find('.form-group').attr("style", "display:block");
                                $('#inputPriorityAndBlockSize').find('input').val('');
                                if ($(e.target).parent().find('td').eq(1).find('option:selected').attr("name") === "ad") {
                                    $('#inputPriorityAndBlockSize').find('.form-group').eq(2).attr("style", "display:none");
                                    $('#inputPriorityAndBlockSize').find('.form-group').eq(3).attr("style", "display:none");
                                }
                                else if ($(e.target).parent().find('td').eq(1).find('option:selected').attr("name") === "da") {
                                    $('#inputPriorityAndBlockSize').find('.form-group').eq(0).attr("style", "display:none");
                                    $('#inputPriorityAndBlockSize').find('.form-group').eq(1).attr("style", "display:none");
                                }
                                //$('#setPriorityAndBlockSize').attr("disabled","true");
                                //$('#inputPriorityAndBlockSize').modal({backdrop: 'static', keyboard: false});
                                $('#dev_uid_label').html($(e.target).parent().find('td').eq(0).attr('uid'));
                                $('#inputPriorityAndBlockSize').modal('show');
                            }
                            if ($(e.target).prev().find('option:selected').attr("name") === "1553b") {
                                $(e.target).find('option').not('[name="ROOT"],[name="selectIO"]').remove();
                            }
                            if ($(e.target).prev().find('option:selected').attr("name") != "1553b") {
                                if ($(e.target).prev().find('option:selected').attr("type") === "deviceIO")
                                    $(e.target).find('option').not('[name="ROOT"],[name="#"],[name="RT"],[name="selectIO"],[type="bus"][name!="1553b"]').remove();
                                else if ($(e.target).prev().find('option:selected').attr("type") != "deviceIO") {
                                    if ($(e.target).prev().find('option:selected').attr("name") === "can") {
                                        $(e.target).find('option').not('[name="ROOT"],[name="#"],[name="RT"],[name="selectIO"]').remove();
                                    }
                                    else if ($(e.target).prev().find('option:selected').attr("name") === "RT") {
                                        $(e.target).find('option').not('[name="ROOT"],[name="#"],[name="1553b"],[name="selectIO"]').remove();
                                    }
                                    else if ($(e.target).prev().find('option:selected').attr("type") === "bus") {
                                        $(e.target).find('option').not('[name="ROOT"],[name="#"],[name="RT"],[name="can"],[name="selectIO"]').remove();
                                    }
                                }
                            }
                        }
                        //$('#listControl option[name=' + m_name + '][uid=' + m_uid + ']').remove();
                        $(e.target).find('option[type="deviceIO"]').each(function () {
                            var name = $('#configModelDesk tbody').find('option:selected[name=' + $(this).attr("name") + '][uid=' + $(this).attr("uid") + ']').attr("name");
                            var uid = $('#configModelDesk tbody').find('option:selected[name=' + $(this).attr("name") + '][uid=' + $(this).attr("uid") + ']').attr("uid");
                            // console.log(name + '|' + uid);
                            if (name != undefined && uid != undefined) {
                                $(this).parent().find('option[name=' + name + '][uid=' + uid + ']').remove();
                            }
                        });

                        $(e.target).find('option[type="bus"]').each(function () {
                                //console.log($(this).html());
                                var channel = $(this).attr("channel");
                                if (channel != undefined) {
                                    var node = $('#configModelDesk tbody').find('option:selected[name=' + $(this).attr("name") + '][uid=' + $(this).attr("uid") + '][channel=' + $(this).attr("channel") + ']');
                                    var uid = node.attr("uid");
                                    var name = node.attr("name");
                                }
                                if (channel != undefined && uid != undefined && name != undefined) {
                                    $(e.target).find('option[name=' + name + '][uid=' + uid + '][channel=' + channel + ']').remove();
                                }
                                console.log(name + '|' + uid + '|' + channel)
                            }
                        );
                        //若RT已经分配
                        if ($(e.target).prev().find('option:selected').attr("name") == "RT") {
                            var RT_uid=$(e.target).prev().find('option:selected').attr("uid");
                            var RT_name=$(e.target).prev().find('option:selected').attr("name");
                            var uid_1553="";
                            $('#configModelDesk tbody').find('option:selected[name=' +RT_name + '][uid=' +RT_uid + ']').each(function(){
                                if($(this).parent().parent().next().find('option:selected[name="1553b"]').length!=0){
                                    uid_1553=$(this).parent().parent().next().find('option:selected[name="1553b"]').attr("uid");
                                }
                            });
                            if(uid_1553!=""){
                                $(e.target).find('option').not('[uid='+uid_1553+']').remove();
                            }
                        }

                        $(e.target).find('option[name="ROOT"]').each(function () {
                            //对前面已经选择ROOT的情况下删除所有其它的ROOT
                            var node = $('#configModelDesk tbody').find('option:selected[name="ROOT"]');
                            console.log(node.length);
                            if (node.length != 0) {
                                if ($(this).html() !== node.eq(0).html()) {
                                    $(this).remove();
                                }
                            }
                            //对于前一个selected做出选择
                            var name = $(this).parent().parent().prev().attr("name");
                            console.log(name);

                            if (name !== "device") {
                                name = $(this).parent().parent().prev().find('option:selected').attr("name");
                                var uid = $(this).parent().parent().prev().find('option:selected').attr("uid");
                                console.log(name);
                                var num = 0;
                                var arry_tmp=[];
                                $('#configModelDesk tbody').find('option:selected[name=' + name + '][uid!='+uid+']').each(function () {
                                    if ($(this).parent().parent().next().find('option:selected').attr("name") === "ROOT") {
                                        if(arry_tmp.indexOf(uid)===-1){
                                            num++;
                                            arry_tmp.push(uid);
                                        }
                                    }
                                });
                                //arry_tmp=[];
                                console.log(num);
                                for (var i = 0; i < createModel.cpuUnitArray.length; i++) {
                                    var num_tmp = num;
                                    for (var j = 0; j < createModel.cpuUnitArray[i].getPortArray().length; j++) {
                                        if (createModel.cpuUnitArray[i].getPortArray()[j].getSupportIO() === name) {
                                            num_tmp--;
                                        }
                                    }
                                    if (num_tmp === 0) {
                                        var uid = createModel.cpuUnitArray[i].getUid();
                                        console.log(uid);
                                        $(this).parent().find('option[uid=' + uid + '][name="ROOT"]').remove();

                                    }
                                }
                            }

                        });
                    }

                    else if ($(e.target)[0].tagName === "SELECT") {
                        console.log('enter select');
                        $(e.target).parent().attr("style", "background-color: rgba(255,69,0,0.2)");
                        //$(e.target).parent().empty();
                        //$(e.target).parent().html($('#listControl').html());
                        //var name=$(e.target).find('option:selected').attr("name");
                        // var uid=$(e.target).find('option:selected').attr("uid");
                        // if(name==="ad"||name==="da")$('#listControl').find('option[name='+name+'][uid='+uid+']').remove();
                        console.log('exit select');
                        //if($('#configModelDesk tbody').find('option[name="ad"]').length!=0){
                        //    $(e.target).find('option[name='+m_name+'][uid='+m_uid+']').remove();
                        //}
                        //$('#configModelDesk tbody').find('option[name="#"]').attr("selected","true");

                    }
                    //if(){

                    //}
                    //$(e.target).child().eq(0).attr("style", "width:" + $(e.target).width);
                    //}
                    // });

                    //var t = event.srcElement.innerHTML;
                    //$(e.target).html($("#listControl").html());
                    //event.srcElement.children[0].value = t;
                    //$(e.target).child().eq(0).attr("style","width:"+$(e.target).width);
                })
            }
        );
    }
    var clearAllIOSelectOptions = function () {
        $('#configModelDesk').find('td[name!="device"]').html('');
    }
    var createEntityDataFormArray = function (isProjectExisted, projectListNum) {
        //直接创建电子数据表格，遍历整个配置表
        $('#configList').find('tbody tr').each(function () { //一行一张电子数据表格，第一列必须为设备
            if ($(this).find('td').eq(0).attr("name") != "device")return;
            createEntityDataForm.clearIOSymbolArray();
            ///将model内的数据导入到电子数据表格中
            var dNode = new createEntityDataForm.createDeviceSymbol;
            dNode.uid = $(this).find('td').eq(0).attr("uid");
            $(this).find('td[name!="device"]').each(function () {
                var IONode = new createEntityDataForm.createIOSymbolNode;
                if ($(this).html() != "") {
                    IONode.type = $(this).find('option:selected').attr("type");
                    IONode.name = $(this).find('option:selected').attr("name");
                    IONode.uid = $(this).find('option:selected').attr("uid");
                    IONode.channel = $(this).find('option:selected').attr("channel");
                    if (IONode.type != undefined && IONode.name != undefined && IONode.uid != undefined) {
                        console.log(IONode.type + "|" + IONode.name + "|" + IONode.uid);
                        createEntityDataForm.IOSymbolArray.push(IONode);
                    }
                }
            });
            var dataForm = new createEntityDataForm.createNewDataForm(dNode, createEntityDataForm.IOSymbolArray);
            createEntityDataForm.dataFormArray.push(dataForm);
        });
        var dataFormArrayObject = new createEntityDataForm.createDataFormArray;
        arrayDeepCopy(dataFormArrayObject.dataFormArray, createEntityDataForm.dataFormArray);
        if (isProjectExisted === false) {
            createEntityDataForm.dataFormArrayHistory.push(dataFormArrayObject);
        }
        else {
            createEntityDataForm.dataFormArrayHistory[projectListNum] = dataFormArrayObject;
        }
        console.log(JSON.stringify(createEntityDataForm.dataFormArrayHistory));

    }
    var reSetOptionValue = function () {
        var i = "1";
        $('#select_scheme').find('option[value!="0"]').each(function () {
            $(this).attr("value", i);
            i++;
        });
    }
    var createXMLDoc = function (dataFormHistoryLocation, dataFormNumber) {
        var XMLDoc = buildXMLConfigFile.createNewXMLDoc(dataFormHistoryLocation, dataFormNumber, "sparc");
        //console.log(buildXMLConfigFile.serializeXMLDoc(XMLDoc));
        return XMLDoc;
    }
    var arrayDeepCopy = function (arrayTarget, arraySource) {
        for (var i = 0; i < arraySource.length; i++) {
            arrayTarget[i] = arraySource[i];
        }
    }
    var configDeskToFullScreen = function () {
        //$('#console').attr("style","display:none");
        $('#section5').animate({
            width: '1330px',
            height: '550px',
        });

    }
    return {
        viewInit: viewInit,
    }
})