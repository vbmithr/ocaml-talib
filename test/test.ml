open Talib

let main size =
  let input = FA.create size in
  let output = FA.create size in
  FA.fill input 100.;
  let start, nb_elts =
    MA.(compute ~src:input ~dst:output ~period:10 ~kind:SMA ()) in
  Printf.printf "input_size = %d, start = %d, nb_elts = %d\n" size start nb_elts;
  for i = start to nb_elts - 1 do
    try assert (output.{i} = 100.) with _ -> prerr_int i;
  done

let () =
  if Array.length Sys.argv < 2 then main (4096 - 4096)
  else main @@ int_of_string Sys.argv.(1)
