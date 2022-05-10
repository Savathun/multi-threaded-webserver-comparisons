use std::io::prelude::*;
use std::net::TcpListener;
use std::net::TcpStream;
extern crate futures;
use futures::executor::ThreadPoolBuilder;

fn main() {
    let listener = TcpListener::bind("localhost:80").unwrap();

    let mut pool_builder = ThreadPoolBuilder::new();
    pool_builder.pool_size(100);
    let pool = pool_builder.create().expect("threadpool creation failed");

    for stream in listener.incoming() {
        let stream = stream.unwrap();

        // spawning each connection in a new thread asynchronously
        pool.spawn_ok(async {
            handle_connection(stream).await;
        });
    }
}

async fn handle_connection(mut stream: TcpStream) {
    // Read the first 1024 bytes of data from the stream
    let mut buffer = [0; 1024];
    stream.read(&mut buffer).unwrap();

    let response = format!("HTTP/1.1 200 OK\r\n\r\n{}", "Hello");

    stream.write(response.as_bytes()).unwrap(); // write response
    stream.flush().unwrap();
}