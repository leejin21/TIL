# 7.1 라이프사이클 메서드의 이해

**Will** 접두사: 어떤 작업을 작동하기 **전**에 실행되는 메서드

**Did** 접두사: 어떤 작업을 작동한 **후**에 실행되는 메서드

## Lifecycle Categories

마운트, 업데이트, 언마운트로 나뉨.

### Mount(마운트)

DOM이 생성되고 웹 브라우저상에서 나타나는 것.

-   마운트할 때 호출하는 메서드

    컴포넌트 만들기

    ⇒ `construtor`: 컴포넌트를 새로 만들 때마다 호출되는 클래스 생성자 메서드

    ⇒ `getDerivedStateFromProps`: props에 있는 값을 state에 넣을 때 사용하는 메서드 ❓

    ⇒ `render`: 우리가 준비한 UI를 렌더링하는 메서드

    ⇒ `componentDidMount`: 컴포넌트가 웹 브라우저상에 나타난 후 호출하는 메서드

    ‼️ render가 componentDidMount 보다 앞선다는 걸 기억하자 ‼️

### Update(업데이트)

-   업데이트를 하는 총 4가지 경우
    1. props가 바뀔 때
    2. state가 바뀔 때
    3. 부모 컴포넌트가 리렌더링될 때(props, state가 바뀌지 않아도 무조건)
    4. this.forceUpdate로 강제로 렌더링을 트리거할 때
-   업데이트할 때 호출하는 메서드

    업데이트를 발생시키는 요인(props 변경, state 변경, 부모 컴포넌트 리렌더링)

    ⇒ `getDerivedStateFromProps`
    : 마운트 과정에서도 호출되는 메서드. 업데이트가 시작하기 전에도 호출됨. props의 변화에 따라 state 값에도 변화를 주고 싶을 때 사용함.

    ⇒ `shouldComponentUpdate`
    : 컴포넌트가 리렌더링을 해야 할 지 말아야 할 지를 결정하는 메서드. true 혹은 false 반환, true: 다음 라이프사이클 메서드 계속 실행, false: 작업 중지(컴포넌트 리렌더링 X).
    IF 특정 함수에서 this.forceUpdate() 함수를 호출한다면 이 과정을 생략하고 바로 render 함수를 호출.

    ⇒ `render`
    : 컴포넌트를 리렌더링

    ⇒ `getSnapshotBeforeUpdate`
    : 컴포넌트 변화를 DOM에 반영하기 바로 전에 호출하는 메서드

    ⇒ `componentDidUpdate`
    : 컴포넌트의 업데이트 작업이 끝난 후 호출하는 메서드

    ‼️ getSnapshotBeforeUpdate가 render **이후, DOM에 반영 직전임** ‼️

### Unmount(언마운트)

마운트의 반대 과정. 컴포넌트를 DOM에서 제거.

-   언마운트할 때 호출하는 메서드

    언마운트하기

    ⇒ `componentWillUnmount`
    : 컴포넌트가 웹 브라우저상에서 사라지기 전에 호출하는 메서드

    ‼️ render 안 거침 ‼️

# 7.2 라이프사이클 메서드 살펴보기

## render 함수

```jsx
render(){...}
```

라이프사이클 메서드 중 유일한 필수 메서드. **컴포넌트 모양새를 정의함.**

메서드 안에서 this.props와 this.state에 접근 가능, 리액트 요소를 반환.

아무것도 보여주고 싶지 않으면 → null이나 false값 반환

## constructor 메서드

```jsx
constructor(props){...}
```

컴포넌트의 생성자 메서드. **컴포넌트를 만들 때 처음으로 실행됨**. 초기 state를 정할 수 있음.

## getDerivedStateFromProps 메서드

```jsx
static getDerivedStateFromProps(nextProps, prevState) {...}
```

**props로 받아 온 값을 state에 동기화시키는 용도**로 사용. 컴포넌트가 mount될 때와 update될 때 호출.

원래 있는 것. 따로 설정할 필요는 없는데, 혹시나 라이프사이클 중간에 뭔가를 건드려야 할 상황이 발생할 경우를 생각해서 저자가 설명해 둔 것 같음(비중도 크지 않음).
props가 바뀔 때 컴포넌트가 리렌더링되는 부분을 설명해 주는 메서드.

## componentDidMount 메서드

```jsx
componentDidMount(){...}
```

컴포넌트 만들고 첫 렌더링을 다 마친 후 실행함.

-   이 안에서 대체로

## shouldComponentUpdate 메서드

```jsx
shouldComponentUpdate(nextProps, nextState){...}
```

이 메서드 안에서

-   현재 props와 state: this.props와 this.state로 접근
-   새로 설정될 props 또는 state는 nextProps, nextState로 접근 가능

**프로젝트 성능을 최적화**할 때 이 메서드에서 false를 반환하는 경우를 둠(for 리렌더링 방지)

## getSnapshotBeforeUpdate 메서드

```jsx
getSnapshotBeforeUpdate(prevProps, prevState) {...}
```

render에서 만들어진 결과물이 브라우저에 실제로 반영되기 직전에 호출됨.

반환값은 componentDIdUpdate에서 3번째 파라미터인 snapshot 값으로 전달받을 수 있음.  
⇒ 주로 업데이트하기 직전의 값을 참고할 일이 있을 때 활용됨.

## componentDidUpdate 메서드

```jsx
componentDidUpdate(prevProps, prevState, snapshot) {...}
```

리렌더링을 완료한 후 실행.

업데이트가 끝난 직후: DOM 관련 처리를 해도 됨(왜?)

prevProps, prevState를 사용해 컴포넌트의 이전 데이터에 접근 가능.

getSnapShotBeforeUpdate에서 반환한 값이 세번째 param으로 snapshot을 전달받을 수 있음.

## componentWillUnmount 메서드

```jsx
componentWillUnmount(){...}
```

컴포넌트를 DOM에서 제거할 때 실행됨.

componentDidMount에서 등록한 이벤트, 타이머, 직접 생성한 DOM은 여기서 제거 작업을 해야 함.

## componentDidCatch 메서드

```jsx
componentDidCatch(error, info){...}
```

컴포넌트 리렌더링 도중에 발생한 에러를 잡아서 오류 UI를 보여줄 수 있게 함.

나중에 실제 에러가 발생했을 때 서버 API를 호출해서 따로 수집할 수도 있음(log).

# 7.3 라이프사이클 메서드 사용하기

## 예제 코드

-   예제 코드 (LifeCycleSample.js)

    ```jsx
    ////////////////////////////////////////////////
    /*
     * EXPLANATION
     1. 각 라이프사이클 메서드를 실행할 때마다 콘솔 디버거에 기록하고, 부모 컴포넌트에서 props로 색상을 받아 버튼을 누르면 state.number 값을 1씩 더함.
     2. getDerivedStateProps는 부모에게서 받은 color 값을 state에 동기화하고 있음. 
     3. getSnapshotBeforeUpdate는 DOM에 변화가 일어나기 직전의 색상 속성을 snapshot 값으로 반환하여 이것을 componentDidMount에서 조회할 수 있도록 했음.
     4. + shouldComponentUpdate 메서드에서 state.number 값의 마지막 자리 수가 4이면 리렌더링을 취소하도록 함.
     */
    ////////////////////////////////////////////////
    import React, { Component } from "react";
    ////////////////////////////////////////////////
    class LifeCycleSample extends Component {
        /*
            * 라이프사이클 메서드 종류
            getDerivedStateFromProps
            componentDidMount
            shouldComponentUpdate
            componentWillUnmount
            getSnapshotBeforeUpdate
            componentDidUpdate
    
            * MOUNT할 때 호출 순서
            constructor
            getDerivedStateFromProps
            render
            componentDidMount
    
            * UPDATE할 때 호출 순서
            getDerivedStateFromProps
            shouldComponentUpdate
            render
            getSnapshotBeforeUpdate
            componentDidUpdate
    
            * UNMOUNT할 때 호출 순서
            componentWillUnmount
    
        */
        state = {
            number: 0,
            color: null,
        };

        myRef = null;

        constructor(props) {
            super(props);
            console.log("constructor");
        }

        static getDerivedStateFromProps(nextProps, prevState) {
            // ?
            console.log("getDerivedStateFromProps");
            if (nextProps.color !== prevState.color) {
                return { color: nextProps.color };
            }
            return null;
        }

        componentDidMount() {
            console.log("componentDidMount");
        }

        shouldComponentUpdate(nextProps, nextState) {
            console.log("shouldComponentUpdate", nextProps, nextState);
            // 숫자의 일의 자리 수가 4면 리렌더링하지 않음.
            return nextState.number % 10 !== 4;
        }

        componentWillUnmount() {
            console.log("componentWillUnmount");
        }

        handleClick = () => {
            this.setState({
                number: this.state.number + 1,
            });
        };

        getSnapshotBeforeUpdate(prevProps, prevState) {
            console.log("getSnapshotBeforeUpdate");
            if (prevProps.color !== this.props.color) {
                return this.myRef.style.color;
            }
            return null;
        }

        componentDidUpdate(prevProps, prevState, snapshot) {
            console.log("componentDidUpdate", prevProps, prevState);
            if (snapshot) {
                console.log("업데이트되기 직전 색상: ", snapshot);
            }
        }

        render() {
            console.log("render");

            const style = {
                color: this.props.color,
            };

            return (
                <div>
                    <h1 style={style} ref={(ref) => (this.myRef = ref)}>
                        {this.state.number}
                    </h1>
                    <p>color: {this.state.color}</p>
                    <button onClick={this.handleClick}>더하기</button>
                </div>
            );
        }
    }

    export default LifeCycleSample;
    ```

-   예제 코드 (App.js)

    ```jsx
    function getRandomColor() {
        return "#" + Math.floor(Math.random() * 16777215).toString(16);
    }

    class App extends Component {
        state = {
            color: "#000000",
        };
        handleClick = () => {
            this.setState({ color: getRandomColor() });
        };
        render() {
            return (
                <div>
                    <button onClick={this.handleClick}>랜덤 색상</button>
                    <LifeCycleSample color={this.state.color}></LifeCycleSample>
                </div>
            );
        }
    }
    ```

## 에러 잡아내기

-   예제 코드(ErrorBoundary.js)

    ```jsx
    import React, { Component } from "react";

    class ErrorBoundary extends Component {
        state = {
            error: false,
        };
        componentDidCatch(error, info) {
            this.setState({
                error: true,
            });
            console.log({ error, info });
        }
        render() {
            if (this.state.error) return <div>에러가 발생했습니다!</div>;
            return this.props.children;
        }
    }

    export default ErrorBoundary;
    ```

# 7.4 정리

이 메서드들은 third party 라이브러리를 사용하거나 DOM을 직접 건드려야 하는 상황에서 유용.

11장에서 컴포넌트 업데이트 성능 개선하는 shouldComponentUpdate가 중요하게 사용됨.
