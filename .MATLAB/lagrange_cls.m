classdef lagrange_cls
    properties
        div  %次数
        x    %待求值点
        xi   %节点
        yi   %节点值
        fi   %待求点值
        f    %插值表达式 
        fx   %准确表达式 
    end
    
    methods
        function obj=lagrange_cls(xi,yi,opts)    %构造函数
            arguments
                xi =[0,1,2];
                yi =[0,1,4];
                opts.fx=[];
                opts.x=1;
            end
            obj.x=opts.x;
            obj.xi=xi;
            obj.yi=yi;
            obj.fx=opts.fx;
            obj.fi=lagrange_cls.calcu(obj.x,obj.xi,obj.yi);
            obj.f=lagrange_cls.calcu_x(obj.xi,obj.yi);
            obj.div=lagrange_cls.getDiv(obj.f);
        end

        function draw(obj,x,xi,f,yi,fx)   %画图函数
            arguments
                obj lagrange_cls
                x =obj.x
                xi =obj.xi
                f =obj.f
                yi =obj.yi
                fx=obj.fx
            end
            m=min(min(x),min(xi));
            n=max(max(x),max(xi));
            mm=m-2*(n-m);
            nn=n+2*(n-m);
            F=matlabFunction(f);
            arr_x=mm:(nn-mm)/1000:nn;
            arr_f=F(arr_x);
            if isempty(fx)
                plot(arr_x,arr_f,'y',xi,yi,':*');
                title(string(f));
            else
                Fx=matlabFunction(fx);
                arr_fx=Fx(arr_x);
                plot(arr_x,arr_f,'g',xi,yi,'-o',arr_x,arr_fx,'b');
            end
        end

    end

    methods(Static)
        function fi=calcu(x,xi,yi)     %计算待求值点函数值函数
            fi=zeros(size(x));
            len=length(yi);
            for i=1:len
                z=ones(size(x));
                for j=1:len
                    if i~=j
                        z=z.*(x-xi(j))/(xi(i)-xi(j));
                    end
                end
                fi=fi+z*yi(i);
            end
        end

        function f=calcu_x(xi,yi)    %计算插值表达式函数
            f=0;
            syms x;
            len=length(yi);
            for i=1:len
                z=1;
                for j=1:len
                    if i~=j
                        z=z.*(x-xi(j))/(xi(i)-xi(j));
                    end
                end
                f=f+z*yi(i);
            end

        end

        function div=getDiv(f)     %获取插值表达式次数函数
            syms x;
            div=polynomialDegree(f,x);
        end

        

    end
end