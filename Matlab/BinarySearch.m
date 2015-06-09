function [ Index ] = BinarySearch( Vector, Value )
   n=size(Vector,1);
   first = 0;
   last = n - 1;
   middle = (first+last)/2;
  
   while( first <= last )
      if ( Vector(middle) < Value &&  Vector(middle+1) > Value )
        Index = middle;
        break;
      elseif ( Vector(middle) < Value )
        first = middle + 1;        
      else
        last = middle - 1;
      end
      middle = uint32((first + last)/2);
   end

   if ( first > last )
     Index = -1;
   end


