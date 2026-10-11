classdef newton_interpolation
    properties
        xi          %节点
        yi          %节点值
        x           %待求值点
        fi          %待求值点函数值
        f           %插值函数
        didf_q_table  %差商表
        fx0_n       %f[x0,x1,...,xi]向量
        ri          %rnx约值
        didf_c_f_table
        didf_c_b_table
    end

    methods
        function obj=newton_interpolation(xi,yi,opts)
            arguments
                xi=[0,1,2]
                yi=[0,1,4]
                opts.x=[]
            end

            obj.xi=xi;
            obj.yi=yi;
            if isempty(opts.x)
            else
                obj.x=opts.x;
            end
            obj.didf_q_table=divided_difference_q_table(obj,obj.xi,obj.yi);
            obj.fx0_n=get_arr_of_fx0_2_fxn(obj,obj.didf_q_table);
            obj.fi=calcu_fi(obj,obj.x,obj.xi,obj.fx0_n);
            obj.ri=calcu_rix(obj,obj.x,obj.xi,obj.fx0_n);
            obj.f=calcu_f(obj,obj.xi,obj.fx0_n);
            obj.didf_c_f_table=calcu_didf_c_f_table(obj,obj.xi,obj.yi);
            obj.didf_c_b_table=calcu_didf_c_b_table(obj,obj.xi,obj.yi);
        end

        function didf_q_table=divided_difference_q_table(obj,xi,yi)
            arguments
                obj newton_interpolation
                xi=[0,1,2]
                yi=[0,1,4]
            end

            len=length(xi);
            didf_q_table=zeros(len,len+1);
            for i=1:len
                didf_q_table(i,1)=xi(i);
                didf_q_table(i,2)=yi(i);
            end

            for i=3:len+1             %列
                for j=i-1:len         %行
                    didf_q_table(j,i)=(didf_q_table(j,i-1)-didf_q_table(j-1,i-1))/(didf_q_table(j,1)-didf_q_table(j-i+2,1));
                end

            end

        end

        function fx0_n=get_arr_of_fx0_2_fxn(obj,didf_q_arr,opts)
            arguments
                obj newton_interpolation
                didf_q_arr =[]
                opts.sz=0
            end
            
            if opts.sz<=0 || opts.sz>size(didf_q_arr,2)
                opts.sz=size(didf_q_arr,1);
            end

            fx0_n=zeros(1,opts.sz);
            for i=1:opts.sz
                fx0_n(i)=didf_q_arr(i,i+1);
            end
        end
        
        function fi=calcu_fi(obj,x,xi,fx0_n)
            arguments
                obj newton_interpolation
                x =obj.x
                xi =obj.xi
                fx0_n =obj.fx0_n
            end
            len=length(x);
            fi=zeros(1,len);
            count_fx0_n=length(fx0_n);
            fi=fi+fx0_n(1);
            for i=2:count_fx0_n
                z=ones(1,len);
                for j=2:i
                    z=z.*(x-xi(j-1));
                end
                fi=fi+fx0_n(i).*z;
            end

        end
        
        function ri=calcu_rix(obj,x,xi,fx0_n)
            arguments
                obj newton_interpolation
                x =obj.x
                xi =obj.xi
                fx0_n =obj.fx0_n
            end
            len=length(x);
            count_fx0_n=length(fx0_n);
            z=ones(1,len);
            for i=1:count_fx0_n
                z=z.*(x-xi(i));
            end
            ri=fx0_n(i).*z;
            ri=abs(ri);
        end
        
        function f=calcu_f(obj,xi,fx0_n)
            arguments
                obj newton_interpolation
                xi =obj.xi
                fx0_n =obj.fx0_n
            end
            syms x;
            count_fx0_n=length(fx0_n);
            f=fx0_n(1);
            for i=2:count_fx0_n
                z=1;
                for j=2:i
                    z=z*(x-xi(j-1));
                end
                f=f+fx0_n(i)*z;
            end

        end

        function didf_c_f_table=calcu_didf_c_f_table(obj,xi,yi)
            arguments
                obj newton_interpolation
                xi =obj.xi
                yi =obj.yi
            end
            
            len=length(xi);
            didf_c_f_table=zeros(len,len+2);
            for i=1:len
                didf_c_f_table(i,1)=i;
                didf_c_f_table(i,2)=xi(i);
                didf_c_f_table(i,3)=yi(i);
            end
            for i=1:len-1
                for j=1:len-i
                    didf_c_f_table(j,i+3)=didf_c_f_table(j+1,i+2)-didf_c_f_table(j,i+2);
                end
            end
        end

        function didf_c_b_table=calcu_didf_c_b_table(obj,xi,yi)
            arguments
                obj newton_interpolation
                xi=obj.xi
                yi=obj.yi
            end

            len=length(xi);
            didf_c_b_table=zeros(len,len+2);
            for i=1:len
                didf_c_b_table(i,1)=i;
                didf_c_b_table(i,2)=xi(i);
                didf_c_b_table(i,3)=yi(i);
            end
            for i=1:len-1
                for j=1:len-i
                    didf_c_b_table(len-j+1,i+3)=didf_c_b_table(len-j+1,i+2)-didf_c_b_table(len-j,i+2);
                end
            end
        end
    end
end

%测试数据
%xi=[0.4,0.55,0.65,0.8,0.9,1.05]
%yi=[0.41075,0.57815,0.69675,0.88811,1.02652,1.25382]
%xi=[4000,4500,5000,5500,6000,6500,7000,7500,8000,8500,9000,9500,10000,10500,11000]
%yi=[1.38,1.48,1.58,1.69,1.81,1.94,2.10,2.28,2.50,2.76,3.06,3.41,3.83,4.33,4.93]
