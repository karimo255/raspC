$(window).ready(function() {


    var cpu_speed=7600;

    /* common */

    var settings_div = $('<div class="settings"/>');

    var settings_speed_label = $('<label/>');    
    settings_speed_label.text('Speed');

    var settings_speed = $('<input class="settings_speed" type="text" name="settings_speed" value="'+cpu_speed+'"/>'); 

    var settings_interface_label = $('<label> Interface </label>');    

    var settings_interface = $('<select class="settings_interface" type="text" name="settings_interface" />');        
    
    var button=$('<button class="btn btn-primary" />');
    button.text('Apply');
    settings_div.append(settings_speed_label).append(settings_speed).append($('<br>'));
    var settings_fa = $('<i class="fa fa-wrench" />');
    $('.halter').append(settings_div).append(settings_fa);
    $('.halter-net-live').find('.settings').append(settings_interface_label).append(settings_interface);
    $('.settings').append(button);
//

/* display/hide settings div */
$('.fa-wrench').click(function(){
    $(this).parents('.halter').find('.settings').toggle();
});




var canvas_width = $(".halter").width()+1;
$(window).resize(function(){
    canvas_width = $(".halter").width()+1;
});

$('select').change(function(){
    var obj={};
    obj.request ="interface";
    obj.interface=$(this).val();
    sendObject(obj);
});


$('.legend i').click(function(){
    switch($.trim($(this).parents("p").text())){
        /* cpu time*/
        case "user":
        cpu_user= cpu_user?0:1;
        cpu_user?$(this).parents("p").css({"opacity":"1"}):$(this).parents("p").css({"opacity":"0.3"});
        break;
        case "system":
        cpu_system= cpu_system?0:1;
        cpu_system?$(this).parents("p").css({"opacity":"1"}):$(this).parents("p").css({"opacity":"0.3"});
        break;
        case "idle":
        cpu_idle= cpu_idle?0:1;
        cpu_idle?$(this).parents("p").css({"opacity":"1"}):$(this).parents("p").css({"opacity":"0.3"});
        break;                                    
        case "wait":
        cpu_wait= cpu_wait?0:1;
        cpu_wait?$(this).parents("p").css({"opacity":"1"}):$(this).parents("p").css({"opacity":"0.3"});
        break;
        /* network*/            
        case "rx":
        rx= rx?0:1;
        rx?$(this).parents("p").css({"opacity":"1"}):$(this).parents("p").css({"opacity":"0.3"});
        break;
        case "tx":
        tx= tx?0:1;
        tx?$(this).parents("p").css({"opacity":"1"}):$(this).parents("p").css({"opacity":"0.3"});
        break;
        case "total":
        total= total?0:1;
        total?$(this).parents("p").css({"opacity":"1"}):$(this).parents("p").css({"opacity":"0.3"});
        break;
        /* cpu freq */                                    
        case "cpu0":
        cpu0= cpu0?0:1;
        cpu0?$(this).parents("p").css({"opacity":"1"}):$(this).parents("p").css({"opacity":"0.3"});
        break;
        case "cpu1":
        cpu1= cpu1?0:1;
        cpu1?$(this).parents("p").css({"opacity":"1"}):$(this).parents("p").css({"opacity":"0.3"});
        break;
        case "cpu2":
        cpu2= cpu2?0:1;
        cpu2?$(this).parents("p").css({"opacity":"1"}):$(this).parents("p").css({"opacity":"0.3"});
        break;
        case "cpu3":
        cpu3= cpu3?0:1;
        cpu3?$(this).parents("p").css({"opacity":"1"}):$(this).parents("p").css({"opacity":"0.3"});
        break;
        /* ram usage*/   
        case "free":
        ram_free= ram_free?0:1;
        ram_free?$(this).parents("p").css({"opacity":"1"}):$(this).parents("p").css({"opacity":"0.3"});
        break;   
        case "used":
        ram_used= ram_used?0:1;
        ram_used?$(this).parents("p").css({"opacity":"1"}):$(this).parents("p").css({"opacity":"0.3"});
        break;  
        case "cached":
        ram_cached= ram_cached?0:1;
        ram_cached?$(this).parents("p").css({"opacity":"1"}):$(this).parents("p").css({"opacity":"0.3"});
        break; 
        case "shared":
        ram_shared= ram_shared?0:1;
        ram_shared?$(this).parents("p").css({"opacity":"1"}):$(this).parents("p").css({"opacity":"0.3"});
        break; 
        case "buffers":
        ram_buffers= ram_buffers?0:1;
        ram_buffers?$(this).parents("p").css({"opacity":"1"}):$(this).parents("p").css({"opacity":"0.3"});
        break;                                                                                
    }
    $('.halter legend ul').hide();
});


//

/* color */

var farben=["red","green","tomato",
"blue","yellow","black","sienna",
"turquoise","teal","skyblue","palevioletred","orangered",
"orange","olive","tan","salmon","thistle","seagreen"];
var color_palette = $('<ul/>');
for (var i = farben.length - 1; i >= 0; i--) {
    var li = $('<li/>');
    li.css({"background-color":farben[i]});
    color_palette.append(li);
}


$('.legend p').append(color_palette);

$('.legend p').click(function(e){
    if($(e.target).is('i') || $(e.target).is('span') ){
        return false;
    }
    $(this).find('ul').toggle();

});

var set_color = function(name,color){
    switch(name){
        /* cpu time */
        case "user":
        cpu_user_color=color;
        break;
        case "system":
        cpu_system_color=color;
        break;
        case "idle":
        cpu_idle_color=color;
        break;                                    
        case "wait":
        cpu_wait_color=color;
        break;  
        /* network */          
        case "rx":
        rx_color=color;
        break;
        case "tx":
        tx_color=color;
        break;
        case "total":
        total_color=color;
        break;                                    
        case "cpu0":
        cpu0_color=color;
        break;            
        case "cpu1":
        cpu1_color=color;
        break;
        case "cpu2":
        cpu2_color=color;
        break;
        case "cpu3":
        cpu3_color=color;
        break; 
        case "used":
        ram_used_color=color;
        break;
        case "free":
        ram_free_color=color;
        break; 
        case "cached":
        ram_cached_color=color;
        break;  
        case "buffers":
        ram_buffers_color=color;
        break;  
        case "shared":
        ram_shared_color=color;
        break;                                                                                                 
    }
};

$('.legend li').click(function(){
    $('.halter legend ul').hide();

    var color = $(this).css("background-color");

    $(this).parents('p').css({"color":color});
    set_color($.trim($(this).parents('p').text()),color);

});

$('.legend p').each(function(index){
    var color = farben[Math.round(Math.random()*1000)%farben.length];
    $(this).css({"color":color});
    var name = $.trim($(this).text());
    set_color(name,color);
});

var  handleCpu=function(obj){
    $('.cpu-details .btn').removeClass("btn-danger").addClass("btn-primary");
    $.each( obj, function( key, value ) {

        if(key=="temp"){
            if(value>48){
                classe="btn-danger"; 
                $('.cpu-details .btn').removeClass("btn-primary").addClass("btn-danger");                                   
            }
            $('#cpuTemp').text(value);
        }                   
    });
}
var  handleRam=function(obj){

    $.each( obj, function( key, value ) {
        $('.bar[label=' + key + ']').find(".value").animate({
            height: (value*210)/925
        },2);
    });
}

var handleCpuInfo=function(obj){
    $('.cpu-info tbody').html("");
    $.each( obj, function( key, value ) {
        var tr=$("<tr/>");
        var th_k=$("<th/>");
        var th_v=$("<th/>");             
        th_k.text(key);
        th_v.text(value);
        tr.append(th_k);
        tr.append(th_v); 
        $('.cpu-info tbody').append(tr);           
    });
}


var handleStorage=function(obj){

    var pieData = [
    {
        value: 0,
        color: "#46BFBD",
        highlight: "#5AD3D1",
        label: "Used"
    },
    {
        value: 0,
        color: "#FDB45C",
        highlight: "#FFC870",
        label: "Free"
    }
    ];
    pieData[0].value=obj.used;
    pieData[1].value=obj.free;

    var ctx = document.getElementById("chart-area").getContext("2d");
    window.myPie = new Chart(ctx).Pie(pieData);

    $('.total').text(obj.total);
}

/*  end common */

window.WebSocket = window.WebSocket || window.MozWebSocket;

var websocket = new WebSocket('ws://192.168.1.6:7681',
  'details');                


var count_client =0;
var cpu_buffer=[];
var ram_buffer=[];
var cpu_freq_buffer=[];
var net_live_buffer=[];

websocket.onopen = function () {
    console.log('verbindung hergestellt');
};

websocket.onerror = function (e) {
    alert(e);
};

var sendObject = function(obj){
    obj = JSON.stringify(obj,null,4);
    websocket.send(obj);
}
var handleNetworkInfo=function(obj){
    var interfaces=$.trim(obj.interfaces);
    console.log(obj);
    var arr =interfaces.split(" ");
    for (var i = arr.length - 1; i >= 0; i--) {
        var option = "<option>"+arr[i]+"</option>";
        $('select').append(option);
    }
    /*
            The (0)st field contains the version information
            of the output that will be changed in future versions of  vnStat
            if the field structure changes. The following fields in order

            1)interface name,

            2) timestamp for today,
            3) rx for today,
            4)  tx  for  today,
            5)  total  for  today, 

            6) average traffic rate for today, 
            11) aver‐age traffic rate for today,

            7) timestamp for current month, 
            8) rx for current  month,
            9) tx for current month, 
            10) total for current month, 
            

            12) all time total rx, 
            13) all  time total tx, 
            14) all time total traffic.*/    


    var oneline = obj.oneline.split(";");
    var keys=[
                "version","interface name",
                "timestamp for today","rx for today",
                "tx for today","total for today","average traffic rate fo today",
                "timestamp for current month","rx for current month",
                "tx for current month","total for current month",
                "aver‐age traffic rate for today","all time total rx",
                "all time total rx","all time traffic tx","all time total traffic"
            ];

    var today=$.map(oneline,function(e,i){        
        return (i>=2 && i<=5)||(i==6 || i==11)?{"key":keys[i],"value":e}:null;
    });
    var today_ul = $("<ul/>");
    for (var i =  0; i < today.length; i++) {
        today_ul.append('<li>'+ today[i].key+ "  :  <b>"+ today[i].value +'</b></li>');
    }

    var month=$.map(oneline,function(e,i){
        return (i>=7 && i<=10)?{"key":keys[i],"value":e}:null;
    });
    var month_ul = $("<ul/>");
    for (var i =  0; i < month.length; i++) {
        month_ul.append('<li>'+ month[i].key+ "  :  <b>"+ month[i].value +'</b></li>');
    } 
       
    var alltime=$.map(oneline,function(e,i){
        return i>=12?{"key":keys[i],"value":e}:null;
    });
    var alltime_ul = $("<ul/>");
    for (var i =  0; i < alltime.length; i++) {
        alltime_ul.append('<li>'+ alltime[i].key+ "  :  <b>"+ alltime[i].value +'</b></li>');
    }       


    $('.net-tarffic').append(today_ul,month_ul,alltime_ul);


}
var c_cpu=0;var c_ram=0;var c_cpu_freq=0;var c_net_live=0;

var prev=0;
websocket.onmessage = function (message) {
    var obj = JSON.parse(message.data);

    for (var i = obj.length - 1; i >= 0; i--) {
        switch (obj[i].request) {
            case "count_client": 
            handleUser(obj[i]);
            break;
            case "cpu-live":
            handleCpu(obj[i].data);
            cpu_buffer[c_cpu]=obj[i].data;
            c_cpu++;
            break;
            case "ram-live":
            ram_buffer[c_ram]=obj[i].data;    
            c_ram++;               
            break;
            case "cpu-freq":
            cpu_freq_buffer[c_cpu_freq]=obj[i].data;    
            c_cpu_freq++;               
            break;            
            case "storage-info":
            handleStorage(obj[i].data);                    
            break;                
            case "cpu-info":
            handleCpuInfo(obj[i].data);                    
            break;    
            case "net-live":
            net_live_buffer[c_net_live]=obj[i].data;  
            $('.status-num p').text(obj[i].data.total-prev+" b/s");
            prev = obj[i].data.total; 
            c_net_live++;                      
            break; 
            case "network-info":
                handleNetworkInfo(obj[i].data);
            break;                           
        }
    }

}






//realtime

var last_value_ram_used=0;
var last_value_ram_free=0;
var last_value_ram_buffers=0;
var last_value_ram_shared=0;
var last_value_ram_cached=0;

//+++++++++++++++++++++++++++++++++++++++++cpu+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
var cpu_speed=7600;

var cpu_user_color;
var cpu_system_color;
var cpu_wait_color;
var cpu_idle_color;


var  cpu_buffer_tmp=[];



var last_value_cpu_user;
var last_value_cpu_system;
var last_value_cpu_idle;
var last_value_cpu_wait;

var cpu_user=1;
var cpu_system=0;
var cpu_idle=0;
var cpu_wait=0;

var cpu_intervall;

var get_cpu_speed = function(){
    return cpu_speed;
};

var handlecpuSpeed=function(){
    $('.halter-cpu').find('.zeit').remove();
    var spped_bar = $('<ul class="zeit"/>');  
    for (var i = 0; i < 3; i++) {
        var li = $('<li/>');
        if(i==2){
            li.text(0);
        }else{
            li.text((get_cpu_speed()/(i+1)/1000)+"S");
        }
        spped_bar.append(li);
    }
    $('.halter-cpu').append(spped_bar);

};
handlecpuSpeed();


var cpu_loop=function(){

    cpu_intervall = setInterval(function(){



        var pallete = $('<div class="pallete"/>');

        $('.halter-cpu').append(pallete);
        pallete.animate({"right":"100%"},get_cpu_speed()*2,"linear");
        if($('.halter-cpu .pallete').size()>2){
            $('.halter-cpu .pallete').eq(0).remove();
        } 

        cpu_buffer_tmp=cpu_buffer;cpu_buffer=[];c_cpu=0;

        if( cpu_user || cpu_system || cpu_idle || cpu_buffers || cpu_wait ){

            var canvas = document.createElement('canvas');


            canvas.height = 240;
            canvas.width = canvas_width;


            var spane = (canvas_width/(cpu_buffer_tmp.length-1));
            var step=0;



            if(cpu_user){
                /*  user*/
                cpu_user_ctx = canvas.getContext("2d");

                cpu_user_ctx.strokeStyle=cpu_user_color;
                cpu_user_ctx.beginPath();



                step=0;


                cpu_user_ctx.lineTo(0,last_value_cpu_user); 


                for (var i = 0; i < cpu_buffer_tmp.length ; i++) {
                    if(i==0){

                    }else{
                        cpu_user_ctx.lineTo(step,240-((cpu_buffer_tmp[i].user*240)/100));  
                    }
                    step=step+spane;
                    if(i==cpu_buffer_tmp.length-2){
                        step=canvas_width;
                    }

                }                

                cpu_user_ctx.stroke();

                last_value_cpu_user=240-((cpu_buffer_tmp[cpu_buffer_tmp.length-1].user*240)/100);
            }
            /* end cpu_user*/

            /* system */
            if(cpu_system){
                cpu_system_ctx = canvas.getContext("2d");

                cpu_system_ctx.strokeStyle=cpu_system_color;
                cpu_system_ctx.beginPath();



                step=0;
                cpu_system_ctx.lineTo(step,last_value_cpu_system); 


                for (var i = 0; i < cpu_buffer_tmp.length ; i++) {
                    if(i==0){

                    }else{
                        cpu_system_ctx.lineTo(step,240-((cpu_buffer_tmp[i].system*240)/100)); 
                    }    
                    step=step+spane;
                    if(i==cpu_buffer_tmp.length-2){
                        step=canvas_width;
                    }

                }                

                cpu_system_ctx.stroke();
                last_value_cpu_system=240-((cpu_buffer_tmp[cpu_buffer_tmp.length-1].system*240)/100);
            }
            /* end system */

            /* idle */
            if(cpu_idle){
                cpu_idle_ctx = canvas.getContext("2d");

                cpu_idle_ctx.strokeStyle=cpu_idle_color;
                cpu_idle_ctx.beginPath();


                var step=0;
                cpu_idle_ctx.lineTo(step,last_value_cpu_idle); 

                for (var i = 0; i < cpu_buffer_tmp.length ; i++) {
                    if(i==0){

                    }else{
                        cpu_idle_ctx.lineTo(step,240-((cpu_buffer_tmp[i].idle*240)/100)); 
                    }    
                    step=step+spane;
                    if(i==cpu_buffer_tmp.length-2){
                        step=canvas_width;
                    }
                }                

                cpu_idle_ctx.stroke();
                last_value_cpu_idle=240-((cpu_buffer_tmp[cpu_buffer_tmp.length-1].idle*240)/100);
            }
            /* end idle */


            /* wait */

            if(cpu_wait){
                cpu_wait_ctx = canvas.getContext("2d");

                cpu_wait_ctx.strokeStyle=cpu_wait_color;
                cpu_wait_ctx.beginPath();

                step=0;
                cpu_wait_ctx.lineTo(step,last_value_cpu_wait); 

                for (var i = 0; i < cpu_buffer_tmp.length ; i++) {
                    if(i==0){

                    }else{
                        cpu_wait_ctx.lineTo(step,240-((cpu_buffer_tmp[i].wait*240)/100)); 
                    }    
                    step=step+spane;
                    if(i==cpu_buffer_tmp.length-2){
                        step=canvas_width;
                    }
                }                

                cpu_wait_ctx.stroke();
                last_value_cpu_wait=240-((cpu_buffer_tmp[cpu_buffer_tmp.length-1].wait*240)/925);
            }            
            /* end wait */
            pallete.append(canvas);
        }


    },get_cpu_speed());

}

cpu_loop();

//+++++++++++++++++++++++++++++++++++++++++ram+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
var ram_speed=7600;

var ram_used_color;
var ram_free_color;
var ram_buffers_color;
var ram_cached_color;
var ram_shared_color;


var  ram_buffer_tmp=[];



var last_value_ram_used;
var last_value_ram_free;
var last_value_ram_shared;
var last_value_ram_cached;
var last_value_ram_buffers;

var ram_used=1;
var ram_free=0;
var ram_shared=0;
var ram_buffers=0;
var ram_cached=0;

var ram_intervall;

var get_ram_speed = function(){
    return ram_speed;
};

var handleRamSpeed=function(){
    $('.halter-ram').find('.zeit').remove();
    var spped_bar = $('<ul class="zeit"/>');  
    for (var i = 0; i < 3; i++) {
        var li = $('<li/>');
        if(i==2){
            li.text(0);
        }else{
            li.text((get_ram_speed()/(i+1)/1000)+"S");
        }
        spped_bar.append(li);
    }
    $('.halter-ram').append(spped_bar);

};
handleRamSpeed();


var ram_loop=function(){

    ram_intervall = setInterval(function(){



        var pallete = $('<div class="pallete"/>');

        $('.halter-ram').append(pallete);
        pallete.animate({"right":"100%"},get_ram_speed()*2,"linear");
        if($('.halter-ram .pallete').size()>2){
            $('.halter-ram .pallete').eq(0).remove();
        } 

        ram_buffer_tmp=ram_buffer;ram_buffer=[];c_ram=0;

        if( ram_used || ram_free || ram_shared || ram_buffers || ram_cached ){

            var canvas = document.createElement('canvas');


            canvas.height = 240;
            canvas.width = canvas_width;


            var spane = (canvas_width/(ram_buffer_tmp.length-1));
            var step=0;



            if(ram_used){
                /*  used*/
                ram_used_ctx = canvas.getContext("2d");

                ram_used_ctx.strokeStyle=ram_used_color;
                ram_used_ctx.beginPath();



                step=0;


                ram_used_ctx.lineTo(0,last_value_ram_used); 


                for (var i = 0; i < ram_buffer_tmp.length ; i++) {
                    if(i==0){

                    }else{
                        ram_used_ctx.lineTo(step,240-((ram_buffer_tmp[i].used*240)/925)); 
                    }
                    step=step+spane;
                    if(i==ram_buffer_tmp.length-2){
                        step=canvas_width;
                    }

                }                

                ram_used_ctx.stroke();

                last_value_ram_used=240-((ram_buffer_tmp[ram_buffer_tmp.length-1].used*240)/925);
            }
            /* end ram_used*/

            /* free */
            if(ram_free){
                ram_free_ctx = canvas.getContext("2d");

                ram_free_ctx.strokeStyle=ram_free_color;
                ram_free_ctx.beginPath();



                step=0;
                ram_free_ctx.lineTo(step,last_value_ram_free); 


                for (var i = 0; i < ram_buffer_tmp.length ; i++) {
                    if(i==0){

                    }else{
                        ram_free_ctx.lineTo(step,240-((ram_buffer_tmp[i].free*240)/925)); 
                    }    
                    step=step+spane;
                    if(i==ram_buffer_tmp.length-2){
                        step=canvas_width;
                    }

                }                

                ram_free_ctx.stroke();
                last_value_ram_free=240-((ram_buffer_tmp[ram_buffer_tmp.length-1].free*240)/925);
            }
            /* end free */

            /* shared */
            if(ram_shared){
                ram_shared_ctx = canvas.getContext("2d");

                ram_shared_ctx.strokeStyle=ram_shared_color;
                ram_shared_ctx.beginPath();


                var step=0;
                ram_shared_ctx.lineTo(step,last_value_ram_shared); 

                for (var i = 0; i < ram_buffer_tmp.length ; i++) {
                    if(i==0){

                    }else{
                        ram_shared_ctx.lineTo(step,240-((ram_buffer_tmp[i].shared*240)/925)); 
                    }    
                    step=step+spane;
                    if(i==ram_buffer_tmp.length-2){
                        step=canvas_width;
                    }
                }                

                ram_shared_ctx.stroke();
                last_value_ram_shared=240-((ram_buffer_tmp[ram_buffer_tmp.length-1].shared*240)/925);
            }
            /* end shared */


            /* cached */
            if(ram_buffers){
                ram_buffers_ctx = canvas.getContext("2d");

                ram_buffers_ctx.strokeStyle=ram_buffers_color;
                ram_buffers_ctx.beginPath();

                step=0;
                ram_buffers_ctx.lineTo(step,last_value_ram_buffers); 

                for (var i = 0; i < ram_buffer_tmp.length ; i++) {
                    if(i==0){

                    }else{
                        ram_buffers_ctx.lineTo(step,240-((ram_buffer_tmp[i].buffers*240)/925)); 
                    }    
                    step=step+spane;
                    if(i==ram_buffer_tmp.length-2){
                        step=canvas_width;
                    }
                }                

                ram_buffers_ctx.stroke();
                last_value_ram_buffers=240-((ram_buffer_tmp[ram_buffer_tmp.length-1].buffers*240)/925);
            }

            if(ram_cached){
                ram_cached_ctx = canvas.getContext("2d");

                ram_cached_ctx.strokeStyle=ram_cached_color;
                ram_cached_ctx.beginPath();

                step=0;
                ram_cached_ctx.lineTo(step,last_value_ram_cached); 

                for (var i = 0; i < ram_buffer_tmp.length ; i++) {
                    if(i==0){

                    }else{
                        ram_cached_ctx.lineTo(step,240-((ram_buffer_tmp[i].cached*240)/925)); 
                    }    
                    step=step+spane;
                    if(i==ram_buffer_tmp.length-2){
                        step=canvas_width;
                    }
                }                

                ram_cached_ctx.stroke();
                last_value_ram_cached=240-((ram_buffer_tmp[ram_buffer_tmp.length-1].cached*240)/925);
            }            
            /* end cached */
            pallete.append(canvas);
        }


    },get_ram_speed());

}

ram_loop();

//++++++++++++++++++++++++++++++++++++++++++++++++cpu freq--------------------------------------------------------------
var cpu_freq_speed=7600;

var cpu0_color;
var cpu1_color;
var cpu2_color;
var cpu3_color;


var  cpu_freq_buffer_tmp=[];

var cpu0_last_value=0;
var cpu1_last_value=0;
var cpu2_last_value=0;
var cpu3_last_value=0;

var cpu0=1;
var cpu1=0;
var cpu2=0;
var cpu3=0;

var cpu_freg_intervall;

var get_cpu_freq_speed = function(){
    return cpu_freq_speed;
};

var handleCpuFregSpeed=function(){
    $('.halter-cpu-freq').find('.zeit').remove();
    var spped_bar = $('<ul class="zeit"/>');  
    for (var i = 0; i < 3; i++) {
        var li = $('<li/>');
        if(i==2){
            li.text(0);
        }else{
            li.text((get_cpu_freq_speed()/(i+1)/1000)+"S");
        }
        spped_bar.append(li);
    }
    $('.halter-cpu-freq').append(spped_bar);

};
handleCpuFregSpeed();


var cpu_freq_loop=function(){

    cpu_freg_intervall = setInterval(function(){



        var pallete = $('<div class="pallete"/>');

        $('.halter-cpu-freq').append(pallete);
        pallete.animate({"right":"100%"},get_cpu_freq_speed()*2,"linear");
        if($('.halter-cpu-freq .pallete').size()>2){
            $('.halter-cpu-freq .pallete').eq(0).remove();
        } 

        cpu_freq_buffer_tmp=cpu_freq_buffer;cpu_freq_buffer=[];c_cpu_freq=0;

        if( cpu0 || cpu1 || cpu2 || cpu3 ){

            var canvas = document.createElement('canvas');


            canvas.height = 240;
            canvas.width = canvas_width;


            var spane = (canvas_width/(cpu_freq_buffer_tmp.length-1));
            var step=0;



            if(cpu0){
                /*  used*/
                cpu0_ctx = canvas.getContext("2d");

                cpu0_ctx.strokeStyle=cpu0_color;
                cpu0_ctx.beginPath();



                step=0;


                cpu0_ctx.lineTo(0,cpu0_last_value); 


                for (var i = 0; i < cpu_freq_buffer_tmp.length ; i++) {
                    if(i==0){

                    }else{
                        cpu0_ctx.lineTo(step,240-cpu_freq_buffer_tmp[i].cpu0); 
                    }
                    step=step+spane;
                    if(i==cpu_freq_buffer_tmp.length-2){
                        step=canvas_width;
                    }

                }                

                cpu0_ctx.stroke();

                cpu0_last_value=240-cpu_freq_buffer_tmp[cpu_freq_buffer_tmp.length-1].cpu0;
            }
            /* end cpu0*/

            /* free */
            if(cpu1){
                cpu1_ctx = canvas.getContext("2d");

                cpu1_ctx.strokeStyle=cpu1_color;
                cpu1_ctx.beginPath();



                step=0;
                cpu1_ctx.lineTo(step,cpu1_last_value); 


                for (var i = 0; i < cpu_freq_buffer_tmp.length ; i++) {
                    if(i==0){

                    }else{
                        cpu1_ctx.lineTo(step,240-cpu_freq_buffer_tmp[i].cpu1); 
                    }    
                    step=step+spane;
                    if(i==cpu_freq_buffer_tmp.length-2){
                        step=canvas_width;
                    }

                }                

                cpu1_ctx.stroke();
                cpu1_last_value=240-cpu_freq_buffer_tmp[cpu_freq_buffer_tmp.length-1].cpu1;
            }
            /* end free */

            /* shared */
            if(cpu2){
                cpu2_ctx = canvas.getContext("2d");

                cpu2_ctx.strokeStyle=cpu2_color;
                cpu2_ctx.beginPath();


                var step=0;
                cpu2_ctx.lineTo(step,cpu2_last_value); 

                for (var i = 0; i < cpu_freq_buffer_tmp.length ; i++) {
                    if(i==0){

                    }else{
                        cpu2_ctx.lineTo(step,240-cpu_freq_buffer_tmp[i].cpu2); 
                    }    
                    step=step+spane;
                    if(i==cpu_freq_buffer_tmp.length-2){
                        step=canvas_width;
                    }
                }                

                cpu2_ctx.stroke();
                cpu2_last_value=240-cpu_freq_buffer_tmp[cpu_freq_buffer_tmp.length-1].cpu2;
            }
            /* end shared */


            /* cached */
            if(cpu3){
                cpu3_ctx = canvas.getContext("2d");

                cpu3_ctx.strokeStyle=cpu3_color;
                cpu3_ctx.beginPath();

                step=0;
                cpu3_ctx.lineTo(step,cpu3_last_value); 

                for (var i = 0; i < cpu_freq_buffer_tmp.length ; i++) {
                    if(i==0){

                    }else{
                        cpu3_ctx.lineTo(step,240-cpu_freq_buffer_tmp[i].cpu3);
                    }    
                    step=step+spane;
                    if(i==cpu_freq_buffer_tmp.length-2){
                        step=canvas_width;
                    }
                }                

                cpu3_ctx.stroke();
                cpu3_last_value=240-cpu_freq_buffer_tmp[cpu_freq_buffer_tmp.length-1].cpu3;
            }
            /* end cached */
            pallete.append(canvas);
        }


    },get_cpu_freq_speed());

}

cpu_freq_loop();


//++++++++++++++++++++++++++++++++++++++++++++++++net live--------------------------------------------------------------
var net_live_speed=7600;

var rx_color;
var tx_color;
var total_color;


var  net_live_buffer_tmp=[];

var rx_last_value=0;
var tx_last_value=0;
var total_last_value=0;

var rx=1;
var tx=0;
var total=0;

var net_live_intervall;

var get_net_live_speed = function(){
    return net_live_speed;
};

var handleNetLiveSpeed=function(){
    $('.halter-net-live').find('.zeit').remove();
    var spped_bar = $('<ul class="zeit"/>');  
    for (var i = 0; i < 3; i++) {
        var li = $('<li/>');
        if(i==2){
            li.text(0);
        }else{
            li.text((get_net_live_speed()/(i+1)/1000)+"S");
        }
        spped_bar.append(li);
    }
    $('.halter-net-live').append(spped_bar);

};
handleNetLiveSpeed();


var net_live_loop=function(){

    net_live_intervall = setInterval(function(){



        var pallete = $('<div class="pallete"/>');

        $('.halter-net-live').append(pallete);
        pallete.animate({"right":"100%"},get_net_live_speed()*2,"linear");
        if($('.halter-net-live .pallete').size()>2){
            $('.halter-net-live .pallete').eq(0).remove();
        } 

        net_live_buffer_tmp=net_live_buffer;net_live_buffer=[];c_net_live=0;

        if( rx || tx || total ){

            var canvas = document.createElement('canvas');


            canvas.height = 240;
            canvas.width = canvas_width;


            var spane = (canvas_width/(net_live_buffer_tmp.length-1));
            var step=0;



            if(rx){
                /*  used*/
                rx_ctx = canvas.getContext("2d");

                rx_ctx.strokeStyle=rx_color;
                rx_ctx.beginPath();



                step=0;


                rx_ctx.lineTo(0,rx_last_value); 


                for (var i = 0; i < net_live_buffer_tmp.length ; i++) {
                    if(i==0){

                    }else{
                        rx_ctx.lineTo(step,240-(((net_live_buffer_tmp[i].rx-net_live_buffer_tmp[i-1].rx)*240)/5120)); 
                    }
                    step=step+spane;
                    if(i==net_live_buffer_tmp.length-2){
                        step=canvas_width;
                    }

                }                

                rx_ctx.stroke();

                rx_last_value=240-(((net_live_buffer_tmp[net_live_buffer_tmp.length-1].rx-net_live_buffer_tmp[net_live_buffer_tmp.length-2].rx)*240)/5120);
            }
            /* end rx*/

            /* free */
            if(tx){
                tx_ctx = canvas.getContext("2d");

                tx_ctx.strokeStyle=tx_color;
                tx_ctx.beginPath();



                step=0;
                tx_ctx.lineTo(step,tx_last_value); 


                for (var i = 0; i < net_live_buffer_tmp.length ; i++) {
                    if(i==0){

                    }else{
                        tx_ctx.lineTo(step,240-(((net_live_buffer_tmp[i].tx-net_live_buffer_tmp[i-1].tx)*240)/5120)); 
                    }

                    step=step+spane;
                    if(i==net_live_buffer_tmp.length-2){
                        step=canvas_width;
                    }
                }                

                tx_ctx.stroke();
                tx_last_value=240-(((net_live_buffer_tmp[net_live_buffer_tmp.length-1].tx-net_live_buffer_tmp[net_live_buffer_tmp.length-2].tx)*240)/5120);
            }
            /* end free */


            /* cached */
            if(total){
                total_ctx = canvas.getContext("2d");

                total_ctx.strokeStyle=total_color;
                total_ctx.beginPath();

                step=0;
                total_ctx.lineTo(step,total_last_value); 

                for (var i = 0; i < net_live_buffer_tmp.length ; i++) {
                    if(i==0){

                    }else{
                       total_ctx.lineTo(step,240-(((net_live_buffer_tmp[i].total-net_live_buffer_tmp[i-1].total)*240)/5120)); 
                   }
                   step=step+spane;
                   if(i==net_live_buffer_tmp.length-2){
                    step=canvas_width;
                }
            }                

            total_ctx.stroke();
            total_last_value=240-(((net_live_buffer_tmp[net_live_buffer_tmp.length-1].total-net_live_buffer_tmp[net_live_buffer_tmp.length-2].total)*240)/5120);
        }
        /* end cached */
        pallete.append(canvas);
    }


},get_net_live_speed());

}

net_live_loop();
//realtime 

/* controll */

/* apply settings */
$('.halter-cpu button').click(function(){
    cpu_freq_speed= $(this).parents('.halter').find('.settings_speed').val();
    $(this).parents('.halter').find('.settings').toggle('slideDown');
    clearTimeout(cpu_intervall);
    cpu_loop();
    handlecpuSpeed();
}); 

$('.halter-cpu-freq button').click(function(){
    cpu_freq_speed= $(this).parents('.halter').find('.settings_speed').val();
    $(this).parents('.halter').find('.settings').toggle('slideDown');
    clearTimeout(cpu_freg_intervall);
    cpu_freq_loop();
    handleCpuFregSpeed();
}); 

$('.halter-ram button').click(function(){
    ram_speed= $(this).parents('.halter').find('.settings_speed').val();
    $(this).parents('.halter').find('.settings').toggle('slideDown');
    clearTimeout(ram_intervall);
    ram_loop();
    handleRamSpeed();
}); 
$('.halter-net-live button').click(function(){
    ram_speed= $(this).parents('.halter').find('.settings_speed').val();
    $(this).parents('.halter').find('.settings').toggle('slideDown');
    clearTimeout(net_live_intervall);
    net_live_loop();
    handleNetLiveSpeed();
});    

});

var tmp_count_client=0;

var handleUser=function(obj){
    var tmp_user;
    tmp_user=$.trim(obj.user_changed);


    var user_info = $.grep(obj.users,function (element,index) {
       return $.trim($.cookie("session_id").substring(24))==$.trim(element.id);
   });
    if($.trim($('.user-name').text())==""){
        $('.user-name').text(user_info[0].user);
    }    

    var other_users = $.grep(obj.users,function (element,index) {
       return $.trim($.cookie("session_id").substring(24))!=$.trim(element.id);
   });

    $('.other_users ul').empty();
    for (var i = other_users.length - 1; i >= 0; i--) {
     var user=$.trim(other_users[i].user);
     $('.other_users ul').append("<li>"+ user +"</li>");
    } 


    if(obj.users[0].gid==100 && $('.manage-user').length==0){
        $('.other_users').append("<h5 class='manage-user'><a href='/admin.html'> manage user </a></h5>"); 
    }


    if(obj.data>tmp_count_client){
        $('.notifications p').text(tmp_user+" has been connected");
        $('.notifications').show();
    }else{
        $('.notifications p').text(tmp_user+" has been disconnected");
        $('.notifications').show();
    }
    setTimeout(function() {
        $('.notifications').hide();
    },1800);
    
    tmp_count_client=obj.data;
}



var deleteSession = function(){
    $.removeCookie("session_id",{ expires:31,path:"/"}) || $.removeCookie("session_id");
    location.reload();
}

$('.logout').click(function(){
    deleteSession();
});