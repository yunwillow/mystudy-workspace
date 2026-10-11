classdef Hermite
    properties
        xi
        yi
        mi
        x
        alpha
        alpha_num
        beta
        beta_num
        Hx
        Hx_num
    end

    methods
        function obj=Hermite(xi,yi,mi,opts)
            arguments
                xi 
                yi 
                mi 
                opts.x=[]
            end
            obj.xi=xi;
            obj.yi=yi;
            obj.mi=mi;
            if verify_valid(obj)
                warning('value invalid!'); 
                error('error!exit!');
            end
            obj.alpha=calcu_alpha(obj);
            obj.beta=calcu_beta(obj);
            obj.Hx=calcu_Hx(obj);
            if opts.x
                obj.x=opts.x;
                obj.alpha_num=calcu_alpha(obj,obj.xi,'x',obj.x);
                obj.beta_num=calcu_beta(obj,obj.xi,'x',obj.x);
                obj.Hx_num=calcu_Hx(obj,obj.xi,obj.yi,obj.mi,obj.alpha_num,obj.beta_num,'x',obj.x);
            end
           
        end

        function vv_count=verify_valid(obj,xi,yi,mi)
            arguments
                obj Hermite
                xi=obj.xi
                yi=obj.yi
                mi=obj.mi
            end
            vv_count=0;
            lenx=length(xi);
            leny=length(yi);
            lenm=length(mi);
            if lenx~=leny || lenm~=lenx
                vv_count=1;
            end
            dip=xi(2)-xi(1);
            for i=3:lenx
                if xi(i)-xi(i-1)~=dip && isnumeric(xi)
                    vv_count=1;
                end
            end
        end

        function alpha=calcu_alpha(obj,xi,opts)
            arguments
                obj Hermite
                xi=obj.xi
                opts.x=[]
            end
            
            len=length(xi);
            if opts.x
                alpha=zeros(1,len);
                x=opts.x;
            else
                syms x;
            end
            for j=1:len
                lj=1;
                sigma_x=0;
                for i=1:len
                    if i~=j
                        sigma_x=sigma_x+1./(xi(j)-xi(i));
                        lj=lj.*(x-xi(i))./(xi(j)-xi(i));
                    end
                end
                alpha(j)=(1-2.*(x-xi(j)).*sigma_x).*lj.*lj;
            end
        end

        function beta=calcu_beta(obj,xi,opts)
            arguments
                obj Hermite
                xi=obj.xi
                opts.x=[]
            end
            
            len=length(xi);
            if opts.x
                beta=zeros(1,len);
                x=opts.x;
            else
                syms x
            end
            for j=1:len
                lj=1;
                for i=1:len
                    if i~=j
                        lj=lj.*(x-xi(i))./(xi(j)-xi(i));
                    end
                end
                beta(j)=(x-xi(j)).*lj.*lj;
            end
        end

        function Hx=calcu_Hx(obj,xi,yi,mi,alpha,beta,opts)
            arguments
                obj Hermite
                xi=obj.xi
                yi=obj.yi
                mi=obj.mi
                alpha=obj.alpha
                beta=obj.beta
                opts.x=[]
            end
            Hx=0;
            if opts.x
                lenx=length(opts.x);
                Hx=zeros(1,lenx);
            end
            len=length(xi);
            for i=1:len
               Hx=Hx+yi(i).*alpha(i)+mi(i).*beta(i);
            end
        end
        
        %function Rx=calcu_Rx(obj,Hx,xi,M_d_2n+2_f)
    end
end