% Thesis: Modeling of artificial muscles made of nylon wire 
% Author: Gabriel Silva - 82084 - MEEC - IST Lisbon - 2018/2019 
% Description: Acquire the results from the arduino (general code)

clear
clc
close all

count = 1;
s = serial('COM4');
fopen(s);

% reads the serial port that is connected to the arduino

while 1  
    %set(s,'BaudRate',9600);
    %fprintf(s,'*IDN?')
    out = fscanf(s);
    out_parse = strsplit(out);      % it parses the obtained results
    if length(out) == 0             % closes the object when doesnt read anything
        fclose(s)
        delete(s)
        clear s
        break
    end
    
    % save the obtained results in a structure (pay attention to the position order of the prints, in the arduino code, to save the values correctly)
    
    readings(count).acq_time = str2double(out_parse(1));    % 1st position in the current line: elapsed acquisition time 
    readings(count).pwm = str2double(out_parse(2));         % 2nd position in the current line: PWM value supplied from the arduino
    readings(count).temp_ntc = str2double(out_parse(3));    % 3rd position in the current line: temperature value acquired by the thermistor
    readings(count).dist = str2double(out_parse(4));        % 4th position in the current line: distance value acquired by the sonars
    readings(count).volt = str2double(out_parse(5));        % 5th position in the current line: volatge value acquired by the arduino
    count = count + 1;
end
