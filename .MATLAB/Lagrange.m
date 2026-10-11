function  fi=Lagrange(x,xi,f,symmodle)
    arguments
        x
        xi
        f
        symmodle = false
    end
if symmodle==true
    syms x
end

fi=zeros(size(x));
len=length(f);
for i=1:len
    z=ones(size(x));
    for j=1:len
        if i~=j
            z=z.*(x-xi(j))/(xi(i)-xi(j));
        end
    end
    fi=fi+z*f(i);
end
