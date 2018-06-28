open Lwt;

Graphql_lwt.Server.start(
	~ctx=req => (),
	MySchema.schema
) |> Lwt_main.run;
