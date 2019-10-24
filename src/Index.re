module Layer {
  type size = {
    width: int,
    height: int
  }

  let sizeInitial = {
    width: Webapi.Dom.Window.innerWidth(Webapi.Dom.window),
    height: Webapi.Dom.Window.innerHeight(Webapi.Dom.window)
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
      Webapi.Dom.window
        ->Webapi.Dom.Window.innerWidth
        ->SetWidth
        ->dispatchSize
      
      Webapi.Dom.window
        ->Webapi.Dom.Window.innerHeight
        ->SetHeight
        ->dispatchSize
    };

    React.useEffect0(() => {
      Webapi.Dom.Window.addEventListener("resize", onResize, Webapi.Dom.window);
      Some(() => Webapi.Dom.Window.removeEventListener("resize", onResize, Webapi.Dom.window));
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

let nrOfCurves = 1000
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
