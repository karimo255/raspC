$(window).ready(function() {


    var cpu_speed=6000;

    /* common */

    var settings_div = $('<div class="settings"/>');

    var settings_speed_label = $('<label/>');    
    settings_speed_label.text('Speed');

    var settings_speed = $('<input class="settings_speed" type="text" name="settings_speed"/>');    

    var button=$('<button class="btn btn-primary" />');
    button.text('Apply');
    settings_div.append(settings_speed_label).append(settings_speed).append(button);

    var settings_fa = $('<i class="fa fa-wrench" />');
    $('.halter').append(settings_div).append(settings_fa);

    //

    /* display/hide settings div */
    $('.fa-wrench').click(function(){
        $(this).parents('.halter').find('.settings').toggle();
    });




    var canvas_width = $(".halter").width()+1;


    $('.legend i').click(function(){
        console.log($(this).text());
        switch($.trim($(this).parents("p").text())){
            case "cpu0":
            cpu0= cpu0?0:1;
            cpu0?$(this).parents("p").css({"opacity":"1"}):$(this).parents("p").css({"opacity":"0.3"});
            break;
            case "cpu1":
            console.log('jj');
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

    var farben=["red","green","tomato","blue","yellow","black","sienna","turquoise","teal","skyblue","palevioletred","orangered"];
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
            value: 300,
            color:"#F7464A",
            highlight: "#FF5A5E",
            label: "Total"
        },
        {
            value: 50,
            color: "#46BFBD",
            highlight: "#5AD3D1",
            label: "Used"
        },
        {
            value: 100,
            color: "#FDB45C",
            highlight: "#FFC870",
            label: "Free"
        }
        ];
        pieData[0].value=obj.total;
        pieData[1].value=obj.used;
        pieData[2].value=obj.free;

        var ctx = document.getElementById("chart-area").getContext("2d");
        window.myPie = new Chart(ctx).Pie(pieData);
    }

    /*  end common */

    window.WebSocket = window.WebSocket || window.MozWebSocket;

    var websocket = new WebSocket('ws://192.168.43.88:7681',
      'details');                


    var count_client =0;
    var cpu_buffer=[];
    var ram_buffer=[];
    var cpu_freq_buffer=[];

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
    var c_cpu=0;var c_ram=0;var c_cpu_freq=0;

    websocket.onmessage = function (message) {
        var obj = JSON.parse(message.data);
        //console.log('erhalten obj');
       // console.log(obj); 
       for (var i = obj.length - 1; i >= 0; i--) {
        switch (obj[i].request) {
            case "count_client": 
            checkCount(obj[i].data);
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
        }
    }

}

websocket.onclose = function (close) {

};




//realtime

var last_value_ram_used=0;
var last_value_ram_free=0;
var last_value_ram_buffers=0;
var last_value_ram_shared=0;
var last_value_ram_cached=0;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

var  cpu_buffer_tmp=[]; 

setInterval(function(){




    cpu_buffer_tmp=cpu_buffer;cpu_buffer=[];c_cpu=0;

//cpu
var pallete = $('<div class="pallete"/>');



var canvas = document.createElement('canvas');



canvas.height = 240;
canvas.width = canvas_width;

/*  idle*/
ctx = canvas.getContext("2d");

ctx.strokeStyle="aquamarine";
ctx.fill="#FF0000";
ctx.beginPath();



var spane = canvas_width/(cpu_buffer_tmp.length-1);
var step=0;
for (var i = 0; i < cpu_buffer_tmp.length ; i++) {

    ctx.lineTo(step,240-((cpu_buffer_tmp[i].idle*240)/100)); 
    step=step+spane;
    if(i==cpu_buffer_tmp.length-1){
        step=canvas_width;
    }
}                

ctx.stroke();

/* end idle*/

/* user */

user_ctx = canvas.getContext("2d");

user_ctx.strokeStyle="#FF00FF";
user_ctx.beginPath();


step=0;
for (var i = 0; i < cpu_buffer_tmp.length; i++) {

    user_ctx.lineTo(step,240-((cpu_buffer_tmp[i].user*240)/100)); 
    step=step+spane;
    if(i==cpu_buffer_tmp.length-1){
        step=canvas_width;
    }
}                

user_ctx.stroke();
/* end user */

/* system */

system_ctx = canvas.getContext("2d");

system_ctx.strokeStyle="sienna";
system_ctx.beginPath();


step=0;
for (var i = 0; i < cpu_buffer_tmp.length ; i++) {

    system_ctx.lineTo(step,240-((cpu_buffer_tmp[i].system*240)/100)); 
    step=step+spane;
    if(i==cpu_buffer_tmp.length-1){
        step=canvas_width;
    }
}                

system_ctx.stroke();
/* end system */


/* wait */

wait_ctx = canvas.getContext("2d");

wait_ctx.strokeStyle="teal";
wait_ctx.beginPath();


step=0;
for (var i = 0; i < cpu_buffer_tmp.length ; i++) {

    wait_ctx.lineTo(step,240-((cpu_buffer_tmp[i].wait*240)/100)); 
    step=step+spane;
    if(i==cpu_buffer_tmp.length-1){
        step=canvas_width;
    }
}                

wait_ctx.stroke();
/* end wait */


pallete.append(canvas);

$('.halter-cpu').append(pallete);
pallete.animate({"right":"100%"},cpu_speed*3,"linear");
if($('.halter-cpu .pallete').size()>4){
    $('.halter-cpu .pallete').eq(0).remove();
} 
/* end cpu*/
},cpu_speed);

//+++++++++++++++++++++++++++++++++++++++++ram+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
var ram_speed=6000;

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



var handleRamSpeed=function(){
    $('.halter-ram').find('.zeit').remove();
    var spped_bar = $('<ul class="zeit"/>');  
    for (var i = 0; i < 3; i++) {
        var li = $('<li/>');
        if(i==2){
            li.text(0);
        }else{
            li.text((ram_speed/(i+1)/1000)+"S");
        }
        spped_bar.append(li);
    }
    $('.halter-ram').append(spped_bar);

};
handleRamSpeed();


var ram_loop=function(){

    ram_intervall = setInterval(function(){
//ram


var pallete = $('<div class="pallete"/>');

$('.halter-ram').append(pallete);
pallete.animate({"right":"100%"},ram_speed*3,"linear");
if($('.halter-ram .pallete').size()>3){
    $('.halter-ram .pallete').eq(0).remove();
} 

ram_buffer_tmp=ram_buffer;ram_buffer=[];c_ram=0;

if(ram_free || ram_used || ram_buffers || ram_cached || ram_shared){
    var canvas = document.createElement('canvas');


    canvas.height = 240;
    canvas.width = canvas_width;

    var spane = (canvas_width/(ram_buffer_tmp.length-1));


    if(ram_used){

        /*  used*/
        ram_used_ctx = canvas.getContext("2d");

        ram_used_ctx.strokeStyle=ram_used_color;
        ram_used_ctx.beginPath();



        spane = (canvas_width/(ram_buffer_tmp.length-1));
        var step=0;



        for (var i = 0; i < ram_buffer_tmp.length ; i++) {

            ram_used_ctx.lineTo(step,240-((ram_buffer_tmp[i].used*240)/925)); 
            step=step+spane;
            if(i==ram_buffer_tmp.length-2){
                step=canvas_width;
            }
        }                

        ram_used_ctx.stroke();
        last_value_ram_used=ram_buffer_tmp[ram_buffer_tmp.length-1].used;

    }
    /* end used*/

    /* free */
    if(ram_free){
        ram_free_ctx = canvas.getContext("2d");

        ram_free_ctx.strokeStyle=ram_free_color;
        ram_free_ctx.beginPath();



        step=0;
        for (var i = 0; i < ram_buffer_tmp.length ; i++) {

            ram_free_ctx.lineTo(step,240-((ram_buffer_tmp[i].free*240)/925)); 
            step=step+spane;
            if(i==ram_buffer_tmp.length-1){
                step=canvas_width;
            }
        }                

        ram_free_ctx.stroke();
        /* end free */
        last_value_ram_free=ram_buffer_tmp[ram_buffer_tmp.length-1].free;    
    }
    /* shared */
    if(ram_shared){
        ram_shared_ctx = canvas.getContext("2d");

        ram_shared_ctx.strokeStyle=ram_shared_color;
        ram_shared_ctx.beginPath();


        var step=0;
        for (var i = 0; i < ram_buffer_tmp.length ; i++) {

            ram_shared_ctx.lineTo(step,240-((ram_buffer_tmp[i].shared*240)/925)); 
            step=step+spane;
            if(i==ram_buffer_tmp.length-1){
                step=canvas_width;
            }
        }                

        ram_shared_ctx.stroke();
        last_value_ram_shared=ram_buffer_tmp[ram_buffer_tmp.length-1].shared;

        /* end shared */
    }

    /* cached */
    if(ram_cached){
        ram_cached_ctx = canvas.getContext("2d");

        ram_cached_ctx.strokeStyle=ram_cached_color;
        ram_cached_ctx.beginPath();

        step=0;
        for (var i = 0; i < ram_buffer_tmp.length ; i++) {

            ram_cached_ctx.lineTo(step,240-((ram_buffer_tmp[i].cached*240)/925));
            step=step+spane;
            if(i==ram_buffer_tmp.length-1){
                step=canvas_width;
            }
        }                

        ram_cached_ctx.stroke();
        /* end cached */
        last_value_ram_cached=ram_buffer_tmp[ram_buffer_tmp.length-1].cached;

    }


    /* buffers */
    if(ram_buffers){
        ram_buffers_ctx = canvas.getContext("2d");

        ram_buffers_ctx.strokeStyle=ram_buffers_color;
        ram_buffers_ctx.beginPath();


        step=0;
        for (var i = 0; i < ram_buffer_tmp.length ; i++) {

            ram_buffers_ctx.lineTo(step,240-((ram_buffer_tmp[i].buffers*240)/925));
            step=step+spane;
            if(i==ram_buffer_tmp.length-1){
                step=canvas_width;
            }
        }                

        ram_buffers_ctx.stroke();
        /* end buffers */
        last_value_ram_buffers=ram_buffer_tmp[ram_buffer_tmp.length-1].buffers;

    }

    pallete.append(canvas);


    /* end ram*/
}

},ram_speed);

}

ram_loop();

//++++++++++++++++++++++++++++++++++++++++++++++++cpu freq--------------------------------------------------------------
var cpu_freq_speed=6000;

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
        pallete.animate({"right":"100%"},get_cpu_freq_speed()*3,"linear");
        if($('.halter-cpu-freq .pallete').size()>3){
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


                cpu0_ctx.lineTo(step,cpu0_last_value); 


                for (var i = 0; i < cpu_freq_buffer_tmp.length ; i++) {

                    cpu0_ctx.lineTo(step,240-cpu_freq_buffer_tmp[i].cpu0); 
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

                    cpu1_ctx.lineTo(step,240-cpu_freq_buffer_tmp[i].cpu1); 
                    step=step+spane;
                    if(i==cpu_freq_buffer_tmp.length-1){
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

                    cpu2_ctx.lineTo(step,240-cpu_freq_buffer_tmp[i].cpu2); 
                    step=step+spane;
                    if(i==cpu_freq_buffer_tmp.length-1){
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

                    cpu3_ctx.lineTo(step,240-cpu_freq_buffer_tmp[i].cpu3);
                    step=step+spane;
                    if(i==cpu_freq_buffer_tmp.length-1){
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



//realtime 

/* controll */

/* apply settings */
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

});


