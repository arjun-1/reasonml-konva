module Layer {
  open Webapi.Dom.Window
  let window = Webapi.Dom.window
  type size = {
    width: int,
    height: int
  }

  let sizeInitial = {
    width: window->innerWidth,
    height: window->innerHeight
  }

  type sizeAction =
    | SetWidth(int)
    | SetHeight(int);

  let sizeReducer = (state, action) => switch(action) {
    | SetWidth(width) => {...state, width}
    | SetHeight(height) => {...state, height}
  };

  [@react.component]
  let make = (~children) => {
    let (stateSize, dispatchSize) = React.useReducer(sizeReducer, sizeInitial);

    let onResize = _ => {
      window
        ->innerWidth
        ->SetWidth
        ->dispatchSize
      
      window
        ->innerHeight
        ->SetHeight
        ->dispatchSize
    };

    React.useEffect0(() => {
      window|>addEventListener("resize", onResize);
      Some(() => window|>removeEventListener("resize", onResize));
    });

    <Konva.Stage width={stateSize.width} height={stateSize.height}>
      <Konva.Layer>
        children
      </Konva.Layer>
    </Konva.Stage>
  }
}

let randomInt = () => Js.Math.random_int(0, Layer.sizeInitial.height) |> Js.Int.toFloat
let randomPoint = () => Bezier.{x: randomInt(), y: randomInt()}
let randomInitialPoints = () => Bezier.{
  p1: randomPoint(),
  p2: randomPoint(),
  p3: randomPoint(),
  p4: randomPoint(),
}

let nrOfCurves = 200
let curves = nrOfCurves
  -> Relude.Array.makeWithIndex(_ => randomInitialPoints())
  |>Array.map(initialPoints => <Bezier initialPoints />)
  |>React.array

ReactDOMRe.renderToElementWithId(
  <Layer>
    curves
  </Layer>,
  "root"
);
