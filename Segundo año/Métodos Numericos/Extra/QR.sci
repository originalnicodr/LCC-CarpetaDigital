function [Q,R]=QR(A)
    m=size(A,1);
    Q=zeros(m,m);
    R=zeros(m,m);
    for k=1:m
       // disp(k,'K = ')
        temp=0;
        for i=1:k-1
            //disp(i,'i = ')
            temp=temp + (((A(:,k))'*Q(:,i))*Q(:,i));//(Q(:,i)'*Q(:,i) norma de Q al cuadrado es 1 porque es ortonormal
        end
        //R(k,k)=sqrt((A(:,k)-temp)'*((A(:,k)-temp)));
        Q(:,k)=(A(:,k)-temp)/norm(A(:,k)-temp,'fro') //(A(:,k)-temp)/R(k,k);//normaliza
        //for j=k+1:m
        //    R(k,j)=Q(:,k)'*A(:,j);
        //end
        R=Q'*A
    end
//    for j=1:m//normalizacion
//        Q(:,j)=Q(:,j)/sqrt(Q(:,j)'*Q(:,j))
//    end
endfunction

A = [12 -51 4; 6 167 -68; -4 24 -41]
B=[1, 2, 3; 4, 5, 6; 7, 8, 9]
