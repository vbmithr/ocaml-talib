open Talib

let main () =
  let size = 10 in
  let inbuf = Array.create_float size in
  let outbuf = Array.create_float size in
  Array.fill inbuf 0 size 100. ;
  let start =
    MA.compute ~inbuf ~outbuf ~period:1 ~kind:SMA in
  Printf.printf "input_size = %d, start = %d\n" size start (* ; *)
  (* for i = 0 to size - 1 do
   *   Printf.printf "%.2f " outbuf.(i)
   * done ;
   * print_endline "" *)

let () = main ()
